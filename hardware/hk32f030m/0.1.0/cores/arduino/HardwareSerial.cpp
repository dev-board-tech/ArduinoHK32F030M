/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#include <stdio.h>
#include "Arduino.h"
#include "HardwareSerial.h"

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
    USART_InitTypeDef USART_InitStruct;
	serial_t _serial;

	HardwareSerial Serial1;
	void serialEvent1() __attribute__((weak));

// Constructors ////////////////////////////////////////////////////////////////
HardwareSerial::HardwareSerial(uint32_t _rx, uint32_t _tx, uint32_t _rts, uint32_t _cts) {
  init(_rx, _tx, _rts, _cts);
}

HardwareSerial::HardwareSerial(HalfDuplexMode_t halfDuplex) {
    USART_HalfDuplexCmd(USART1, halfDuplex == HALF_DUPLEX_ENABLED ? ENABLE : DISABLE);
}

HardwareSerial::HardwareSerial(uint32_t _rxtx) {
  init(-1, _rxtx);
}

void HardwareSerial::init(uint32_t _rx, uint32_t _tx, uint32_t _rts, uint32_t _cts) {
  if (_rx == _tx) {
    _serial.pin_rx = -1;
  } else {
    _serial.pin_rx = _rx;
  }
  _serial.pin_tx = _tx;
  _serial.pin_rts = _rts;
  _serial.pin_cts = _cts;
  _serial.rx_buff = _rx_buffer;
  _serial.rx_head = 0;
  _serial.rx_tail = 0;
  _serial.tx_buff = _tx_buffer;
  _serial.tx_head = 0;
  _serial.tx_tail = 0;

  USART_StructInit(&USART_InitStruct);
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  // AF config
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

  // PIN_SERIAL_RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // PIN_SERIAL_TX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void USART1_IRQHandler(void) {
  // No Parity error, read byte and store it in the buffer if there is room
  unsigned char c;
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    c = USART_ReceiveData(USART1);
    rx_buffer_index_t i = (unsigned int)(_serial.rx_head + 1) % SERIAL_RX_BUFFER_SIZE;

    // if we should be storing the received character into the location
    // just before the tail (meaning that the head would advance to the
    // current location of the tail), we're about to overflow the buffer
    // and so we don't write the character or advance the head.
    if (i != _serial.rx_tail) {
      _serial.rx_buff[_serial.rx_head] = c;
      _serial.rx_head = i;
    }
  }
}

// Actual interrupt handlers //////////////////////////////////////////////////

/*int HardwareSerial::_tx_complete_irq(serial_t *obj) {
  size_t remaining_data;
  // previous HAL transfer is finished, move tail pointer accordingly
  obj->tx_tail = (obj->tx_tail + obj->tx_size) % SERIAL_TX_BUFFER_SIZE;

  // If buffer is not empty (head != tail), send remaining data
  if (obj->tx_head != obj->tx_tail) {
    remaining_data = (SERIAL_TX_BUFFER_SIZE + obj->tx_head - obj->tx_tail)
                     % SERIAL_TX_BUFFER_SIZE;
    // Limit the next transmission to the buffer end
    // because HAL is not able to manage rollover
    obj->tx_size = min(remaining_data,
                       (size_t)(SERIAL_TX_BUFFER_SIZE - obj->tx_tail));
    uart_attach_tx_callback(obj, _tx_complete_irq, obj->tx_size);
    return -1;
  }

  return 0;
}*/

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud, uint8_t config) {
  uint32_t databits = 0;

  // Manage databits
  switch (config & 0x07) {
    case 0x02:
      databits = 6;
      break;
    case 0x04:
      databits = 7;
      break;
    case 0x06:
      databits = 8;
      break;
    default:
      databits = 0;
      break;
  }

  if ((config & 0x30) == 0x30) {
    USART_InitStruct.USART_Parity = USART_Parity_Odd;
  } else if ((config & 0x20) == 0x20) {
    USART_InitStruct.USART_Parity = USART_Parity_Even;
  } else {
    USART_InitStruct.USART_Parity = USART_Parity_No;
  }

  if ((config & 0x08) == 0x08) {
    USART_InitStruct.USART_StopBits = USART_StopBits_2;
  } else {
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
  }

  switch (databits) {
    case 7:
      USART_InitStruct.USART_WordLength = USART_WordLength_7b;
      break;
    case 8:
      USART_InitStruct.USART_WordLength = USART_WordLength_8b;
      break;
    case 9:
      USART_InitStruct.USART_WordLength = USART_WordLength_9b;
      break;
    default:
    case 0:
      //Error_Handler();
      break;
  }
  
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_BaudRate = baud;

  USART_Init(USART1, &USART_InitStruct);

  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
  // Enable UART1
  USART_Cmd(USART1, ENABLE);	    
  _ready = true;
}

void HardwareSerial::end() {
  _ready = false;
  // wait for transmission of outgoing data
  flush(TX_TIMEOUT);

  USART_Cmd(USART1, DISABLE);	    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
  // PIN_SERIAL_RX
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // PIN_SERIAL_TX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // clear any received data
  _serial.rx_head = _serial.rx_tail;
}

int HardwareSerial::available(void) {
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _serial.rx_head - _serial.rx_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int HardwareSerial::peek(void) {
  if (_serial.rx_head == _serial.rx_tail) {
    return -1;
  } else {
    return _serial.rx_buff[_serial.rx_tail];
  }
}

int HardwareSerial::read(void) {
  //enableHalfDuplexRx();
  // if the head isn't ahead of the tail, we don't have any characters
  if (_serial.rx_head == _serial.rx_tail) {
    return -1;
  } else {
    unsigned char c = _serial.rx_buff[_serial.rx_tail];
    _serial.rx_tail = (rx_buffer_index_t)(_serial.rx_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}

int HardwareSerial::availableForWrite(void) {
  tx_buffer_index_t head = _serial.tx_head;
  tx_buffer_index_t tail = _serial.tx_tail;

  if (head >= tail) {
    return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
  }
  return tail - head - 1;
}

void HardwareSerial::flush() {
  flush(0);
}

void HardwareSerial::flush(uint32_t timeout) {
  // If we have never written a byte, no need to flush. This special
  // case is needed since there is no way to force the TXC (transmit
  // complete) bit to 1 during initialization
  if (_written) {
    /*uint32_t tickstart = HAL_GetTick();
    while ((_serial.tx_head != _serial.tx_tail)) {
      // the interrupt handler will free up space for us
      // Only manage timeout if any
      if ((timeout != 0) && ((HAL_GetTick() - tickstart) >= timeout)) {
        // clear any transmit data
        _serial.tx_head = _serial.tx_tail;
        break;
      }
    }*/
    // If we get here, nothing is queued anymore (DRIE is disabled) and
    // the hardware finished transmission (TXC is set).
  }
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size) {
  _written = true;
  uint8_t i;
  for(i=0; i<size; i++) {
	USART_SendData(USART1, buffer[i]);	
  	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
  }
  /* Block till transmission is completed */
  return i;
}

size_t HardwareSerial::write(uint8_t c) {
  uint8_t buff = c;
  return write(&buff, 1);
}

void HardwareSerial::setRx(uint32_t _rx) {
  //_serial.pin_rx = digitalPinToPinName(_rx);
}

void HardwareSerial::setTx(uint32_t _tx) {
  //_serial.pin_tx = digitalPinToPinName(_tx);
}

void HardwareSerial::setRts(uint32_t _rts) {
  //_serial.pin_rts = digitalPinToPinName(_rts);
}

void HardwareSerial::setCts(uint32_t _cts) {
  //_serial.pin_cts = digitalPinToPinName(_cts);
}

void HardwareSerial::setRtsCts(uint32_t _rts, uint32_t _cts) {
  //_serial.pin_rts = digitalPinToPinName(_rts);
  //_serial.pin_cts = digitalPinToPinName(_cts);
}

void HardwareSerial::setHalfDuplex(void) {
  _serial.pin_rx = -1;
}

bool HardwareSerial::isHalfDuplex(void) const {
  return _serial.pin_rx == -1;
}

void HardwareSerial::enableHalfDuplexRx(void) {
  //if (isHalfDuplex()) {
    // In half-duplex mode we have to wait for all TX characters to
    // be transmitted before we can receive data.
    //flush();
    //if (!_rx_enabled) {
      //_rx_enabled = true;
      //uart_enable_rx(&_serial);
    //}
  //}
}

void HardwareSerial::setRxInvert(void) {
  //_rx_invert = true;
}

void HardwareSerial::setTxInvert(void) {
  //_tx_invert = true;
}

void HardwareSerial::setDataInvert(void) {
  //_data_invert = true;
}

#endif // HAL_UART_MODULE_ENABLED && !HAL_UART_MODULE_ONLY
