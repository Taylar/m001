#ifndef		KEY_H
#define		KEY_H

// key num
#ifndef		KEY_NUM_TYPEDEF
#define		KEY_NUM_TYPEDEF
typedef enum
{
	KEY_S0	= 0,
	KEY_S1,
	KEY_S2,
	KEY_S3,
	KEY_S4,
} key_num_t;

#endif
/*end defineif */

#define		KEY_MAX_NUM					5

typedef struct 
{
	uint8_t	keyPin;
	func *ShortKey;
	func *Hold3sKey;
	func *Hold6sKey;
}bsp_key_define_s;

extern bsp_key_define_s		bspDefineKey[KEY_MAX_NUM];



typedef struct 
{
	bsp_key_define_s	*key;
	void 				(*Init)(void);
	uint8_t				(*ReadState_S0)(void);
	uint8_t				(*ReadState_S1)(void);
	uint8_t				(*ReadState_S2)(void);
	uint8_t				(*ReadState_S3)(void);
	uint8_t				(*ReadState_S4)(void);
}bsp_key_s;

extern const bsp_key_s	bspKey;


// 	Key Init
void BspKeyInit(void);

uint8_t ReadState_S0(void);

uint8_t ReadState_S1(void);

uint8_t ReadState_S2(void);

uint8_t ReadState_S3(void);

uint8_t ReadState_S4(void);

// const bsp_key_s			bspKey = 
// {
// 	.key			= bspDefineKey,
// 	.Init			= BspKeyInit,
// 	.ReadState_S0	= ReadState_S0,
// 	.ReadState_S1	= ReadState_S1,
// 	.ReadState_S2	= ReadState_S2,
// 	.ReadState_S3	= ReadState_S3,
// 	.ReadState_S4	= ReadState_S4,
// };

#endif	//
