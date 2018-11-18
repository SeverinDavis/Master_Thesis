#ifndef CAN_H
#define CAN_H

typedef struct {
  uint8_t identifier;
  uint8_t data[8];
  uint8_t data_length;
} can_message;

can_message can_message_create(uint8_t p_identifier, uint8_t* p_data, uint8_t p_data_length) {
  can_message message;
  message.identifier = p_identifier;
  message.data_length = p_data_length;
  for(uint8_t i = 0; i < p_data_length; i++)
    message.data[i] = p_data[i];

  return message;
}

can_message can_message_copy(can_message p_message) {
  return can_message_create(p_message.identifier, p_message.data, p_message.data_length);
}

void can_message_set_data(uint8_t *p_data, uint8_t p_data_length, can_message* p_message) {
  p_message->data_length = p_data_length;
  for(uint8_t i = 0; i < p_data_length; i++)
    p_message->data[i] = p_data[i];
}

void can_message_set_identifier(uint8_t p_identifier, can_message* p_message) {
  p_message->identifier = p_identifier;
}

#endif