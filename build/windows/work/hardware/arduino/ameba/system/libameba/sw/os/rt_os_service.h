#ifndef _RT_OS_SERVICE_H_
#define _RT_OS_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "basic_types.h"
#include "rt_queue.h"
#include "cmsis_os.h"


typedef void* _sema;

//
// macro functions
//

#define atomic_set(v,i) {cli();((v)->counter = (i));sti();}

#define ASSERT(bool)					do { } while (!(bool))

//
#define RTW_GET_LE16(a) ((u16) (((a)[1] << 8) | (a)[0]))
#define RTW_PUT_LE16(a, val)			\
	do {					\
		(a)[1] = ((u16) (val)) >> 8;	\
		(a)[0] = ((u16) (val)) & 0xff;	\
	} while (0)





//
// extern functions
//

extern void save_and_cli(void);
extern void restore_flags(void);
extern void cli(void);
extern void sti(void);

//
// inline functions
//
static inline u32 _RND4(u32 sz)
{
	u32	val;

	val = ((sz >> 2) + ((sz & 3) ? 1: 0)) << 2;
	
	return val;
}

static inline int ATOMIC_SUB_RETURN(atomic_t *v, int i)
{
	int temp;

	save_and_cli();
	temp = v->counter;
	temp -= i;
	v->counter = temp;
	restore_flags();

	return temp;
}

static inline int ATOMIC_DEC_RETURN(atomic_t *v)
{
	return ATOMIC_SUB_RETURN(v, 1);
}


static inline int ATOMIC_DEC_AND_TEST(atomic_t *v)
{
	return ATOMIC_DEC_RETURN(v) == 0;
}



// time

extern void rtw_udelay_os(int us);
extern void rt_os_mdelay(int ms);


// memory

extern void* rtw_malloc(size_t size);
extern void rtw_free(void* ptr);
extern int rtw_memcmp(void *dst, void *src, u32 sz);

extern void rtw_memcpy(void* dst, void* src, u32 sz);

extern void rtw_memset(void *pbuf, int c, u32 sz);

//
extern void rtw_spinlock_init(_lock *plock);

extern int rtw_create_thread(osThreadDef_t* pthread_def, void (*task)(), void *argument,
        osPriority priority, uint32_t stack_size);

extern void rtw_init_sema(_sema *sema, int count);
extern int rtw_up_sema(_sema *sema);
extern int rtw_down_timeout_sema(_sema *sema, u32 timeout_ms);
extern int rtw_down_sema(_sema *sema);

//
extern int rtw_random(void);
extern void rtw_get_random_bytes(u8 *buf, int len);


extern u32 rtw_get_current_time(void);

//
extern u64 rtw_modular64(u64 n, u64 base);

// Timer
#define MAX_TIMER_ID	16
typedef void (*TIMER_FUN)(void *context);

extern void rtw_init_timer(uint8_t *ptimer_id, TIMER_FUN pfunc,void* cntx, char* name);

#ifdef __cplusplus
}
#endif



#endif