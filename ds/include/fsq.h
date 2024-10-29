#ifndef __FSQ_H__
#define __FSQ_H__

typedef struct fsq fsq_t;

fsq_t *FSQCreate(size_t capacity);
void FSQDestroy(fsq_t *fsq);
void FSQEnqueue(fsq_t *fsq, void *data);
void *FSQDequeue(fsq_t *fsq);


#endif /*__FSQ_H__*/
