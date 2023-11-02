#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdlib.h>
#include <stddef.h>

#include "CustomAssert.h"

typedef long long comparator_t (void *, void *);

enum class BufferErrorCode {
	NO_BUFFER_ERRORS	= 0,
	NO_BUFFER			= 1,
	BUFFER_ENDED		= 2,
};

template <typename T>
struct Buffer {
  	size_t capacity = 0;
  	size_t currentIndex = 0;

  	T *data = NULL;
};

template <typename T>
BufferErrorCode WriteDataToBuffer (Buffer <T> *buffer, const void *data, size_t dataSize);
template <typename T>
BufferErrorCode InitBuffer 		  (Buffer <T> *buffer, size_t capacity=0);
template <typename T>
BufferErrorCode DestroyBuffer 	  (Buffer <T> *buffer);
template <typename T>
T *FindValueInBuffer 			  (Buffer <T> *buffer, T *value, comparator_t *comparator);

inline BufferErrorCode WriteStringToBuffer (Buffer <char> *buffer, const char *string);

template <typename T>
BufferErrorCode WriteDataToBuffer (Buffer <T> *buffer, const void *data, size_t dataSize) {
  	PushLog (4);

  	custom_assert (buffer, pointer_is_null, BufferErrorCode::NO_BUFFER);
  	custom_assert (data,   pointer_is_null, BufferErrorCode::NO_BUFFER);

  	if (dataSize > buffer->capacity - buffer->currentIndex) {
		if (buffer->capacity == 0)
			buffer->capacity = 1;

		buffer->capacity *= 2;
		buffer->data = (T *) reallocarray (buffer->data, buffer->capacity, sizeof (T));

		if (!buffer->data) {
			RETURN BufferErrorCode::BUFFER_ENDED;
		}
  	}

  	for (size_t dataIndex = 0; dataIndex < dataSize; dataIndex++) {
		buffer->data [buffer->currentIndex++] = ((const T *) data) [dataIndex];
	}

  	RETURN BufferErrorCode::NO_BUFFER_ERRORS;
}

inline BufferErrorCode WriteStringToBuffer (Buffer <char> *buffer, const char *string) {
	return WriteDataToBuffer (buffer, string, sizeof (string));
}

template <typename T>
BufferErrorCode InitBuffer (Buffer <T> *buffer, size_t capacity) {
	PushLog (4);

	custom_assert (buffer, pointer_is_null, BufferErrorCode::NO_BUFFER);

	buffer->capacity = capacity;
	buffer->data = (T *) calloc (buffer->capacity, sizeof (T));

	if (!buffer->data) {
		RETURN BufferErrorCode::NO_BUFFER;
	}

	RETURN BufferErrorCode::NO_BUFFER_ERRORS;
}

template <typename T>
BufferErrorCode DestroyBuffer (Buffer <T> *buffer) {
	PushLog (4);

	custom_assert (buffer, pointer_is_null, BufferErrorCode::NO_BUFFER);

	free (buffer->data);

	RETURN BufferErrorCode::NO_BUFFER_ERRORS;
}

template <typename T>
T *FindValueInBuffer (Buffer <T> *buffer, T *value, comparator_t *comparator) {
	PushLog (3);

	custom_assert (buffer, 	   pointer_is_null, NULL);
	custom_assert (comparator, pointer_is_null, NULL);
	custom_assert (value,      pointer_is_null, NULL);

	for (size_t index = 0; index < buffer->currentIndex; index++) {
		if (!comparator (buffer->data + index, value)) {
			RETURN buffer->data + index;
		}
	}

	RETURN NULL;
}


#endif
