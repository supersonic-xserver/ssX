/* $XFree86$ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef  _VBEXT_
#define  _VBEXT_

extern   void     XGISetDPMS( PXGI_HW_DEVICE_INFO pXGIHWDE , ULONG VESA_POWER_STATE ) ;
extern   void     XGI_GetSenseStatus( PXGI_HW_DEVICE_INFO HwDeviceExtension , PVB_DEVICE_INFO pVBInfo );
extern   void     XGINew_SetModeScratch ( PXGI_HW_DEVICE_INFO HwDeviceExtension , PVB_DEVICE_INFO pVBInfo ) ;
extern   void 	  XGI_ReadVBIOSTablData( UCHAR ChipType , PVB_DEVICE_INFO pVBInfo);
#ifdef WIN2000
extern   BOOLEAN  XGI_DySense( PHW_DEVICE_EXTENSION pHWDE , PUCHAR ujConnectStatus );
#endif /* WIN2000 */

#endif
