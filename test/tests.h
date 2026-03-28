/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef TESTS_H
#define TESTS_H

int fixes_test(void);
int hashtabletest_test(void);
int input_test(void);
int list_test(void);
int misc_test(void);
int signal_logging_test(void);
int string_test(void);
int touch_test(void);
int xfree86_test(void);
int xkb_test(void);
int xtest_test(void);

int protocol_xchangedevicecontrol_test(void);

int protocol_xiqueryversion_test(void);
int protocol_xiquerydevice_test(void);
int protocol_xiselectevents_test(void);
int protocol_xigetselectedevents_test(void);
int protocol_xisetclientpointer_test(void);
int protocol_xigetclientpointer_test(void);
int protocol_xipassivegrabdevice_test(void);
int protocol_xiquerypointer_test(void);
int protocol_xiwarppointer_test(void);
int protocol_eventconvert_test(void);
int xi2_test(void);

#ifndef INSIDE_PROTOCOL_COMMON

extern int enable_XISetEventMask_wrap;
extern int enable_GrabButton_wrap;

#endif /* INSIDE_PROTOCOL_COMMON */

#endif /* TESTS_H */

