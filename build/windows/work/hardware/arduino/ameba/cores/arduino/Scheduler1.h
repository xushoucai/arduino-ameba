/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SCHEDULDER_H_
#define _SCHEDULDER_H_

#include <Arduino.h>

extern "C" {
	typedef void (*SchedulerTask)(void);
	typedef void (*SchedulerParametricTask)(void *);
}

class SchedulerClass1 {
public:
	SchedulerClass1();
	static void startLoop(SchedulerTask task, uint32_t stackSize = 1024);
//	static void start(SchedulerTask task, uint32_t stackSize = 1024);
//	static void start(SchedulerParametricTask task, void *data, uint32_t stackSize = 1024);

	static void yield() { ::yield(); };

};

extern SchedulerClass1 Scheduler1;

#endif

