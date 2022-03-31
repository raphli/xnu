/*
 * Copyright (c) 1998-2021 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 *
 */

#define TEST_HEADERS    0
#define IOKIT_ENABLE_SHARED_PTR

#if TEST_HEADERS

#include <libkern/OSByteOrder.h>
#include <libkern/c++/OSArray.h>
#include <libkern/c++/OSAllocation.h>
#include <libkern/c++/OSBoolean.h>
#include <libkern/c++/OSBoundedArray.h>
#include <libkern/c++/OSBoundedArrayRef.h>
#include <libkern/c++/OSBoundedPtr.h>
#include <libkern/c++/OSCollection.h>
#include <libkern/c++/OSCollectionIterator.h>
#include <libkern/c++/OSContainers.h>
#include <libkern/c++/OSCPPDebug.h>
#include <libkern/c++/OSData.h>
#include <libkern/c++/OSDictionary.h>
#include <libkern/c++/OSEndianTypes.h>
#include <libkern/c++/OSIterator.h>
#include <libkern/c++/OSKext.h>
#include <libkern/c++/OSLib.h>
#include <libkern/c++/OSMetaClass.h>
#include <libkern/c++/OSNumber.h>
#include <libkern/c++/OSObject.h>
#include <libkern/c++/OSOrderedSet.h>
#include <libkern/c++/OSSerialize.h>
#include <libkern/c++/OSSet.h>
#include <libkern/c++/OSSharedPtr.h>
#include <libkern/c++/OSString.h>
#include <libkern/c++/OSSymbol.h>
#include <libkern/c++/OSUnserialize.h>
#include <libkern/c++/OSValueObject.h>
#include <libkern/crypto/aes.h>
#include <libkern/crypto/aesxts.h>
#include <libkern/crypto/crypto_internal.h>
#include <libkern/crypto/des.h>
#include <libkern/crypto/md5.h>
#include <libkern/crypto/register_crypto.h>
#include <libkern/crypto/sha1.h>
#include <libkern/crypto/sha2.h>
#include <libkern/kernel_mach_header.h>
#include <libkern/kext_request_keys.h>
#include <libkern/kxld.h>
#include <libkern/kxld_types.h>
#include <libkern/locks.h>
#include <libkern/mkext.h>
#include <libkern/OSAtomic.h>
#include <libkern/OSBase.h>
#include <libkern/OSDebug.h>
#include <libkern/OSKextLib.h>
#include <libkern/OSKextLibPrivate.h>
#include <libkern/OSReturn.h>
#include <libkern/OSSerializeBinary.h>
#include <libkern/OSTypes.h>
#include <libkern/prelink.h>
#include <libkern/stack_protector.h>
#include <libkern/sysctl.h>
#include <libkern/tree.h>
#include <libkern/zconf.h>
#include <libkern/zlib.h>

#include <IOKit/AppleKeyStoreInterface.h>
#include <IOKit/assert.h>
#include <IOKit/IOBSD.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOCatalogue.h>
#include <IOKit/IOCommand.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/IOCommandPool.h>
#include <IOKit/IOCommandQueue.h>
#include <IOKit/IOConditionLock.h>
#include <IOKit/IOCPU.h>
//#include <IOKit/IODataQueue.h>
#include <IOKit/IODataQueueShared.h>
#include <IOKit/IODeviceMemory.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IODMACommand.h>
#include <IOKit/IODMAController.h>
#include <IOKit/IODMAEventSource.h>
#include <IOKit/IOEventSource.h>
#include <IOKit/IOFilterInterruptEventSource.h>
#include <IOKit/IOHibernatePrivate.h>
#include <IOKit/IOInterleavedMemoryDescriptor.h>
#include <IOKit/IOInterruptAccounting.h>
#include <IOKit/IOInterruptAccountingPrivate.h>
#include <IOKit/IOInterruptController.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOInterrupts.h>
#include <IOKit/IOKernelReporters.h>
#include <IOKit/IOKernelReportStructs.h>
#include <IOKit/IOKitDebug.h>
#include <IOKit/IOKitDiagnosticsUserClient.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/IOKitKeysPrivate.h>
#include <IOKit/IOKitServer.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOLocks.h>
#include <IOKit/IOLocksPrivate.h>
#include <IOKit/IOMapper.h>
#include <IOKit/IOMemoryCursor.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOMultiMemoryDescriptor.h>
#include <IOKit/IONotifier.h>
#include <IOKit/IONVRAM.h>
#include <IOKit/IOPlatformExpert.h>
#include <IOKit/IOPolledInterface.h>
#include <IOKit/IORangeAllocator.h>
#include <IOKit/IORegistryEntry.h>
#include <IOKit/IOReportMacros.h>
#include <IOKit/IOReportTypes.h>
#include <IOKit/IOReturn.h>
#include <IOKit/IOService.h>
#include <IOKit/IOServicePM.h>
#include <IOKit/IOSharedDataQueue.h>
#include <IOKit/IOSharedLock.h>
#include <IOKit/IOStatistics.h>
#include <IOKit/IOStatisticsPrivate.h>
#include <IOKit/IOSubMemoryDescriptor.h>
#include <IOKit/IOSyncer.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/IOTimeStamp.h>
#include <IOKit/IOTypes.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/nvram/IONVRAMController.h>
#include <IOKit/OSMessageNotification.h>
#include <IOKit/platform/AppleMacIO.h>
#include <IOKit/platform/AppleMacIODevice.h>
#include <IOKit/platform/AppleNMI.h>
#include <IOKit/platform/ApplePlatformExpert.h>
#include <IOKit/power/IOPwrController.h>
#include <IOKit/pwr_mgt/IOPM.h>
#include <IOKit/pwr_mgt/IOPMinformee.h>
#include <IOKit/pwr_mgt/IOPMinformeeList.h>
#include <IOKit/pwr_mgt/IOPMLibDefs.h>
#include <IOKit/pwr_mgt/IOPMlog.h>
#include <IOKit/pwr_mgt/IOPMPowerSource.h>
#include <IOKit/pwr_mgt/IOPMPowerSourceList.h>
#include <IOKit/pwr_mgt/IOPMpowerState.h>
#include <IOKit/pwr_mgt/IOPMPrivate.h>
#include <IOKit/pwr_mgt/IOPowerConnection.h>
#include <IOKit/pwr_mgt/RootDomain.h>
#include <IOKit/rtc/IORTCController.h>
#include <IOKit/system.h>
#include <IOKit/system_management/IOWatchDogTimer.h>
#include <math.h>

#endif /* TEST_HEADERS */

#include <sys/sysctl.h>
#include <libkern/c++/OSData.h>
#include <IOKit/IOService.h>
#include <IOKit/IOUserClient.h>
#include "Tests.h"


#if DEVELOPMENT || DEBUG

#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/IOPlatformExpert.h>
#include <IOKit/IOSharedDataQueue.h>
#include <IOKit/IODataQueueShared.h>
#include <IOKit/IOServiceStateNotificationEventSource.h>
#include <IOKit/IOKitKeysPrivate.h>
#include <IOKit/IOKitServer.h>
#include <IOKit/IOBSD.h>
#include <kern/ipc_kobject.h>
#include <libkern/Block.h>
#include <libkern/Block_private.h>
#include <libkern/c++/OSAllocation.h>
#include <libkern/c++/OSBoundedArray.h>
#include <libkern/c++/OSBoundedArrayRef.h>
#include <libkern/c++/OSBoundedPtr.h>
#include <libkern/c++/OSSharedPtr.h>
#include <os/cpp_util.h>

static uint64_t gIOWorkLoopTestDeadline;

static void
TESAction(OSObject * owner, IOTimerEventSource * tes)
{
	if (mach_absolute_time() < gIOWorkLoopTestDeadline) {
		tes->setTimeout(1, kMicrosecondScale);
	}
}

static int
IOWorkLoopTest(int newValue)
{
	IOReturn err;
	uint32_t idx;
	OSSharedPtr<IOWorkLoop> wl;
	OSSharedPtr<IOTimerEventSource> tes;
	OSSharedPtr<IOInterruptEventSource> ies;

	wl = IOWorkLoop::workLoop();
	assert(wl);
	tes = IOTimerEventSource::timerEventSource(kIOTimerEventSourceOptionsPriorityWorkLoop, wl.get(), &TESAction);
	assert(tes);
	err = wl->addEventSource(tes.get());
	assert(kIOReturnSuccess == err);
	clock_interval_to_deadline(100, kMillisecondScale, &gIOWorkLoopTestDeadline);
	for (idx = 0; mach_absolute_time() < gIOWorkLoopTestDeadline; idx++) {
		tes->setTimeout(idx & 1023, kNanosecondScale);
	}
	tes->cancelTimeout();
	wl->removeEventSource(tes.get());

	int value = 3;

	tes = IOTimerEventSource::timerEventSource(kIOTimerEventSourceOptionsDefault, wl.get(), ^(IOTimerEventSource * tes){
		kprintf("wl %p, value %d\n", wl.get(), value);
	});
	err = wl->addEventSource(tes.get());
	assert(kIOReturnSuccess == err);

	value = 2;
	tes->setTimeout(1, kNanosecondScale);
	IOSleep(1);
	wl->removeEventSource(tes.get());

	ies = IOInterruptEventSource::interruptEventSource(wl.get(), NULL, 0, ^void (IOInterruptEventSource *sender, int count){
		kprintf("ies block %p, %d\n", sender, count);
	});

	assert(ies);
	kprintf("ies %p\n", ies.get());
	err = wl->addEventSource(ies.get());
	assert(kIOReturnSuccess == err);
	ies->interruptOccurred(NULL, NULL, 0);
	IOSleep(1);
	ies->interruptOccurred(NULL, NULL, 0);
	IOSleep(1);
	wl->removeEventSource(ies.get());

	return 0;
}

static int
OSCollectionTest(int newValue)
{
	OSSharedPtr<OSArray> array = OSArray::withCapacity(8);
	array->setObject(kOSBooleanTrue);
	array->setObject(kOSBooleanFalse);
	array->setObject(kOSBooleanFalse);
	array->setObject(kOSBooleanTrue);
	array->setObject(kOSBooleanFalse);
	array->setObject(kOSBooleanTrue);

	__block unsigned int index;
	index = 0;
	array->iterateObjects(^bool (OSObject * obj) {
		kprintf("%d:%d ", index, (obj == kOSBooleanTrue) ? 1 : (obj == kOSBooleanFalse) ? 0 : 2);
		index++;
		return false;
	});
	kprintf("\n");

	OSSharedPtr<OSDictionary> dict = IOService::resourceMatching("hello");
	assert(dict);
	index = 0;
	dict->iterateObjects(^bool (const OSSymbol * sym, OSObject * obj) {
		OSString * str = OSDynamicCast(OSString, obj);
		assert(str);
		kprintf("%d:%s=%s\n", index, sym->getCStringNoCopy(), str->getCStringNoCopy());
		index++;
		return false;
	});

	OSSharedPtr<OSSerializer> serializer = OSSerializer::withBlock(^bool (OSSerialize * s){
		return gIOBSDUnitKey->serialize(s);
	});
	assert(serializer);
	IOService::getPlatform()->setProperty("OSSerializer_withBlock", serializer.get());

	OSSharedPtr<OSString> ab = OSString::withCString("abcdef", 2);
	assert(strcmp(ab->getCStringNoCopy(), "ab") == 0);
	OSSharedPtr<OSString> defgh = OSString::withCString("defgh", 10);
	assert(strcmp(defgh->getCStringNoCopy(), "defgh") == 0);
	OSSharedPtr<OSString> zyxwvut = OSString::withCString("zyxwvut", 7);
	assert(strcmp(zyxwvut->getCStringNoCopy(), "zyxwvut") == 0);

	return 0;
}

static int
OSAllocationTests(int)
{
	OSAllocation<int> ints(100, OSAllocateMemory);
	assert(ints);

	{
		int counter = 0;
		for (int& i : ints) {
			i = counter++;
		}
	}

	{
		int counter = 0;
		for (int& i : ints) {
			assert(i == counter);
			++counter;
		}
	}

	OSAllocation<int> arrayZero(100, OSAllocateMemoryZero);
	assert(arrayZero);
	for (const auto& i : arrayZero) {
		assert(i == 0);
	}

	// Make sure we can have two-level OSAllocations
	{
		OSAllocation<OSAllocation<int> > testArray(10, OSAllocateMemory);
		for (int i = 0; i < 10; i++) {
			testArray[i] = OSAllocation<int>(10, OSAllocateMemory);
			for (int j = 0; j < 10; ++j) {
				testArray[i][j] = i + j;
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; ++j) {
				assert(testArray[i][j] == i + j);
			}
		}
	}

	return 0;
}

static int
OSDataAllocationTests(int)
{
	OSDataAllocation<int> ints(100, OSAllocateMemory);
	assert(ints);

	{
		int counter = 0;
		for (int& i : ints) {
			i = counter++;
		}
	}

	{
		int counter = 0;
		for (const int& i : ints) {
			assert(i == counter);
			++counter;
		}
	}

	OSDataAllocation<int> arrayZero(100, OSAllocateMemoryZero);
	assert(arrayZero);
	for (const auto& i : arrayZero) {
		assert(i == 0);
	}

	return 0;
}

static int
OSBoundedArrayTests(int)
{
	OSBoundedArray<int, 5> ints = {0, 1, 2, 3, 4};
	assert(ints.size() == 5);

	{
		int counter = 0;
		for (int& i : ints) {
			i = counter++;
		}
	}

	{
		int counter = 0;
		for (int& i : ints) {
			assert(i == counter);
			++counter;
		}
	}

	return 0;
}

static int
OSBoundedArrayRefTests(int)
{
	OSBoundedArray<int, 5> storage = {0, 1, 2, 3, 4};
	OSBoundedArrayRef<int> ints(storage);
	assert(ints);

	{
		int counter = 0;
		for (int& i : ints) {
			i = counter++;
		}
	}

	{
		int counter = 0;
		for (int& i : ints) {
			assert(i == counter);
			++counter;
		}
	}

	return 0;
}

class OSArraySubclass : public OSArray {
	OSDeclareDefaultStructors(OSArraySubclass);
public:
	static OSSharedPtr<OSArraySubclass> withCapacity(unsigned int inCapacity);
	virtual unsigned int iteratorSize() const APPLE_KEXT_OVERRIDE;
};

OSDefineMetaClassAndStructors(OSArraySubclass, OSArray);

OSSharedPtr<OSArraySubclass>
OSArraySubclass::withCapacity(unsigned int inCapacity)
{
	OSSharedPtr<OSArraySubclass> me = OSMakeShared<OSArraySubclass>();

	if (me && !me->initWithCapacity(inCapacity)) {
		return nullptr;
	}

	return me;
}

unsigned int
OSArraySubclass::iteratorSize() const
{
	unsigned int result = 64;
	// Has to be larger than the OSArray iterator size to prevent out-of-bounds writes
	assert(result >= OSArray::iteratorSize());
	return result;
}

class OSCISubclass : public OSCollectionIterator {
	OSDeclareDefaultStructors(OSCISubclass);
public:
	static OSSharedPtr<OSCISubclass> withCollection(const OSCollection * inColl);
};

OSDefineMetaClassAndStructors(OSCISubclass, OSCollectionIterator);

OSSharedPtr<OSCISubclass>
OSCISubclass::withCollection(const OSCollection * inColl)
{
	OSSharedPtr<OSCISubclass> me = OSMakeShared<OSCISubclass>();

	if (me && !me->initWithCollection(inColl)) {
		return nullptr;
	}

	return me;
}

static int
OSCollectionIteratorTests(int)
{
	OSSharedPtr<OSArray> array = OSArray::withCapacity(0);
	OSSharedPtr<OSString> firstObj = OSString::withCString("test object");
	OSSharedPtr<OSString> secondObj = OSString::withCString("test object 2");
	OSObject * current = NULL;
	OSSharedPtr<OSCollectionIterator> osci = NULL;
	OSSharedPtr<OSCISubclass> osciSubclass = NULL;
	size_t index = 0;
	array->setObject(firstObj);
	array->setObject(secondObj);

	// Test iteration over a normal OSArray
	osci = OSCollectionIterator::withCollection(array.get());
	assert(osci != NULL);

	index = 0;
	while ((current = osci->getNextObject()) != NULL) {
		if (index == 0) {
			assert(current == firstObj);
		} else if (index == 1) {
			assert(current == secondObj);
		} else {
			panic("index out of range");
		}
		index++;
	}

	// Test iteration with a OSCollectionIterator subclass over a normal OSArray
	osciSubclass = OSCISubclass::withCollection(array.get());
	assert(osciSubclass != NULL);

	index = 0;
	while ((current = osciSubclass->getNextObject()) != NULL) {
		if (index == 0) {
			assert(current == firstObj);
		} else if (index == 1) {
			assert(current == secondObj);
		} else {
			panic("index out of range");
		}
		index++;
	}

	// Create the OSArray subclass
	OSSharedPtr<OSArraySubclass> arraySubclass = OSArraySubclass::withCapacity(0);
	arraySubclass->setObject(firstObj);
	arraySubclass->setObject(secondObj);
	// Test iteration over a subclassed OSArray, with a large iterator size
	osci = OSCollectionIterator::withCollection(arraySubclass.get());
	assert(osci != NULL);

	index = 0;
	while ((current = osci->getNextObject()) != NULL) {
		if (index == 0) {
			assert(current == firstObj);
		} else if (index == 1) {
			assert(current == secondObj);
		} else {
			panic("index out of range");
		}
		index++;
	}

	// Test iteration with a OSCollectionIterator subclass over a subclassed OSArray,
	// with a large iterator size.
	osciSubclass = OSCISubclass::withCollection(arraySubclass.get());
	assert(osciSubclass != NULL);

	index = 0;
	while ((current = osciSubclass->getNextObject()) != NULL) {
		if (index == 0) {
			assert(current == firstObj);
		} else if (index == 1) {
			assert(current == secondObj);
		} else {
			panic("index out of range");
		}
		index++;
	}

	return 0;
}

static int
OSBoundedPtrTests(int)
{
	int array[5] = {55, 66, 77, 88, 99};
	OSBoundedPtr<int> begin(&array[0], &array[0], &array[5]);
	OSBoundedPtr<int> end(&array[5], &array[0], &array[5]);

	{
		int counter = 0;
		for (OSBoundedPtr<int> b = begin; b != end; ++b) {
			*b = counter++;
		}
	}

	{
		int counter = 0;
		for (OSBoundedPtr<int> b = begin; b != end; ++b) {
			assert(*b == counter);
			++counter;
		}
	}

	return 0;
}

static int
OSValueObjectTests(int)
{
	struct TrivialTestType {
		int a;
		bool b;
		float c;
	};

	class NonTrivialConstructorTestType
	{
public:
		NonTrivialConstructorTestType() = default;
		int a = 3;
		bool b = true;
		float c = 999.f;
	};

	constexpr auto nearlyEqual = [](float a, float b)
	    {
		    constexpr float epsilon = 0.000001f;
		    const auto diff = a - b;
		    return (diff >= -epsilon) && (diff <= epsilon);
	    };

	// test simple built-in type
	{
		using T = int;
		OSSharedPtr<OSValueObject<T> > test = OSValueObject<T>::create();
		assert(test);
		if (test) {
			assert(test->getRef() == 0);
			assert(test->isEqualTo(0));
			assert(test->getBytesNoCopy());
			assert(test->getBytesNoCopy() == test->getMutableBytesNoCopy());
			assert(test->getLength() == sizeof(T));
		}
	}

	// test trivial aggregate type
	{
		using T = TrivialTestType;
		OSSharedPtr<OSValueObject<T> > test = OSValueObject<T>::create();
		assert(test);
		if (test) {
			const auto *const bytes = reinterpret_cast<const uint8_t*>(test->getBytesNoCopy());
			bool bytesAreZero = true;
			for (size_t byteIndex = 0; byteIndex < test->getLength(); byteIndex++) {
				bytesAreZero &= bytes[byteIndex] == 0;
			}
			assert(bytesAreZero);
		}
	}

	// test aggregate type with non-trivial constructor
	{
		using T = NonTrivialConstructorTestType;
		OSSharedPtr<OSValueObject<T> > test = OSValueObject<T>::create();
		assert(test);
		if (test) {
			const T other;
			assert(test->isEqualTo(other));
			assert(test->getRef().a == other.a);
			assert(test->getRef().b == other.b);
			assert(nearlyEqual(test->getRef().c, other.c));
		}
	}

	// test copying of OSValueObject
	{
		using T = NonTrivialConstructorTestType;
		OSSharedPtr<OSValueObject<T> > test1;
		T valueCopy;
		{
			T value; // declared in sub-scope to ensure instance-independence when it falls out of scope
			value.a = 1;
			value.b = true;
			value.c = 3.f;
			valueCopy = value;
			test1 = OSValueObject<T>::withValue(value);
			assert(test1);
			if (test1) {
				assert(test1->isEqualTo(value));
				assert(test1->getRef().a == value.a);
				assert(test1->getRef().b == value.b);
				assert(nearlyEqual(test1->getRef().c, value.c));
			}
			valueCopy.a = 100;
			test1->getMutableRef().a = valueCopy.a;
		}
		if (test1) {
			OSSharedPtr<OSValueObject<T> > test2 = OSValueObject<T>::withValueObject(test1.get());
			if (test2) {
				assert(test2->isEqualTo(test1.get()));
				assert(test2->getRef().a == valueCopy.a);
				assert(test2->getRef().b == valueCopy.b);
				assert(nearlyEqual(test2->getRef().c, valueCopy.c));
			}
		}
	}

	return KERN_SUCCESS;
}


static int
IOSharedDataQueue_44636964(__unused int newValue)
{
	OSSharedPtr<IOSharedDataQueue> sd = IOSharedDataQueue::withCapacity(DATA_QUEUE_ENTRY_HEADER_SIZE + sizeof(UInt64));
	UInt64 data = 0x11223344aa55aa55;
	UInt32 data2 = 0x44332211;
	UInt32 size = sizeof(UInt32);
	/* enqueue moves tail to end */
	sd->enqueue(&data, sizeof(UInt64));
	/* dequeue moves head to end */
	sd->dequeue(&data, &size);
	/* Tail wraps around, head is still at end */
	sd->enqueue(&data2, sizeof(UInt32));
	/* something in the queue so peek() should return non-null */
	assert(sd->peek() != NULL);
	return KERN_SUCCESS;
}

#if 0
#include <IOKit/IOUserClient.h>
class TestUserClient : public IOUserClient
{
	OSDeclareDefaultStructors(TestUserClient);
	virtual void stop( IOService *provider) APPLE_KEXT_OVERRIDE;
	virtual bool finalize(IOOptionBits options) APPLE_KEXT_OVERRIDE;
	virtual IOReturn externalMethod( uint32_t selector,
	    IOExternalMethodArguments * arguments,
	    IOExternalMethodDispatch * dispatch,
	    OSObject * target,
	    void * reference ) APPLE_KEXT_OVERRIDE;
};

void
TestUserClient::stop( IOService *provider)
{
	kprintf("TestUserClient::stop\n");
}
bool
TestUserClient::finalize(IOOptionBits options)
{
	kprintf("TestUserClient::finalize\n");
	return true;
}
IOReturn
TestUserClient::externalMethod( uint32_t selector,
    IOExternalMethodArguments * arguments,
    IOExternalMethodDispatch * dispatch,
    OSObject * target,
    void * reference )
{
	getProvider()->terminate();
	IOSleep(500);
	return 0;
}
OSDefineMetaClassAndStructors(TestUserClient, IOUserClient);
#endif

static int
IOServiceTest(int newValue)
{
	OSSharedPtr<OSDictionary> matching;
	IONotifier        * note;
	__block IOService * found;

#if 0
	found = new IOService;
	found->init();
	found->setName("IOTestUserClientProvider");
	found->attach(IOService::getPlatform());
	found->setProperty("IOUserClientClass", "TestUserClient");
	found->registerService();
#endif

	matching = IOService::serviceMatching("IOPlatformExpert");
	assert(matching);
	found = nullptr;
	note = IOService::addMatchingNotification(gIOMatchedNotification, matching.get(), 0,
	    ^bool (IOService * newService, IONotifier * notifier) {
		kprintf("found %s, %d\n", newService->getName(), newService->getRetainCount());
		found = newService;
		found->retain();
		return true;
	}
	    );
	assert(note);
	assert(found);
	note->remove();

	note = found->registerInterest(gIOBusyInterest,
	    ^IOReturn (uint32_t messageType, IOService * provider,
	    void   * messageArgument, size_t argSize) {
		kprintf("%p messageType 0x%08x %p\n", provider, messageType, messageArgument);
		return kIOReturnSuccess;
	}).detach();
	assert(note);
	IOSleep(1 * 1000);
	note->remove();
	found->release();

	return 0;
}

static void
OSStaticPtrCastTests()
{
	// const& overload
	{
		OSSharedPtr<OSDictionary> const dict = OSMakeShared<OSDictionary>();
		OSSharedPtr<OSCollection> collection = OSStaticPtrCast<OSCollection>(dict);
		assert(collection == dict);
	}
	{
		OSSharedPtr<OSDictionary> const dict = nullptr;
		OSSharedPtr<OSCollection> collection = OSStaticPtrCast<OSCollection>(dict);
		assert(collection == nullptr);
	}
	// && overload
	{
		OSSharedPtr<OSDictionary> dict = OSMakeShared<OSDictionary>();
		OSDictionary* oldDict = dict.get();
		OSSharedPtr<OSCollection> collection = OSStaticPtrCast<OSCollection>(os::move(dict));
		assert(collection.get() == oldDict);
		assert(dict == nullptr);
	}
	{
		OSSharedPtr<OSDictionary> dict = nullptr;
		OSSharedPtr<OSCollection> collection = OSStaticPtrCast<OSCollection>(os::move(dict));
		assert(collection == nullptr);
		assert(dict == nullptr);
	}
}

static void
OSConstPtrCastTests()
{
	// const& overload
	{
		OSSharedPtr<OSDictionary const> const dict = OSMakeShared<OSDictionary>();
		OSSharedPtr<OSDictionary> dict2 = OSConstPtrCast<OSDictionary>(dict);
		assert(dict2 == dict);
	}
	{
		OSSharedPtr<OSDictionary const> const dict = OSMakeShared<OSDictionary>();
		OSSharedPtr<OSDictionary const> dict2 = OSConstPtrCast<OSDictionary const>(dict);
		assert(dict2 == dict);
	}
	{
		OSSharedPtr<OSDictionary const> const dict = nullptr;
		OSSharedPtr<OSDictionary> dict2 = OSConstPtrCast<OSDictionary>(dict);
		assert(dict2 == nullptr);
	}
	{
		OSSharedPtr<OSDictionary const> const dict = nullptr;
		OSSharedPtr<OSDictionary const> dict2 = OSConstPtrCast<OSDictionary const>(dict);
		assert(dict2 == nullptr);
	}

	// && overload
	{
		OSSharedPtr<OSDictionary const> dict = OSMakeShared<OSDictionary>();
		OSDictionary const* oldDict = dict.get();
		OSSharedPtr<OSDictionary> dict2 = OSConstPtrCast<OSDictionary>(os::move(dict));
		assert(dict == nullptr);
		assert(dict2 == oldDict);
	}
	{
		OSSharedPtr<OSDictionary const> dict = nullptr;
		OSSharedPtr<OSDictionary> dict2 = OSConstPtrCast<OSDictionary>(os::move(dict));
		assert(dict == nullptr);
		assert(dict2 == nullptr);
	}
}

static void
OSDynamicPtrCastTests()
{
	OSSharedPtr<OSDictionary> const dict = OSMakeShared<OSDictionary>();
	{
		OSSharedPtr<OSCollection> collection = OSDynamicPtrCast<OSCollection>(dict);
		assert(collection != nullptr);
	}
	{
		OSSharedPtr<OSArray> array = OSDynamicPtrCast<OSArray>(dict);
		assert(array == nullptr);
		assert(dict != nullptr);
	}
	{
		OSTaggedSharedPtr<OSCollection, OSCollection> taggedDict(dict.get(), OSRetain);
		OSTaggedSharedPtr<OSCollection, OSCollection> collection = OSDynamicPtrCast<OSCollection>(taggedDict);
		assert(collection != nullptr);
	}
	{
		OSTaggedSharedPtr<OSCollection, OSCollection> taggedDict(dict.get(), OSRetain);
		OSTaggedSharedPtr<OSArray, OSCollection> array = OSDynamicPtrCast<OSArray>(taggedDict);
		assert(array == nullptr);
		assert(dict != nullptr);
	}
	{
		OSSharedPtr<OSCollection> collection = OSDynamicPtrCast<OSCollection>(dict);
		assert(collection.get() == OSDynamicCast(OSDictionary, dict.get()));
		OSSharedPtr<OSDictionary> newDict = OSDynamicPtrCast<OSDictionary>(os::move(collection));
		assert(collection == nullptr);
		assert(newDict != nullptr);
		assert(newDict.get() == dict.get());
	}
}


class IOTestUserNotification : public IOUserNotification
{
	OSDeclareDefaultStructors(IOTestUserNotification);
};

OSDefineMetaClassAndStructors(IOTestUserNotification, IOUserNotification)

struct IOUserNotificationTestThreadArgs {
	IOTestUserNotification * userNotify;
	IOLock * lock;
	size_t * completed;
	size_t iterations;
};

static bool
IOUserNotificationMatchingHandler( void * target __unused,
    void * ref __unused, IOService * newService __unused, IONotifier * notifier __unused )
{
	return true;
}

static void
IOUserNotificationTestThread(void * arg, wait_result_t result __unused)
{
	IOUserNotificationTestThreadArgs * threadArgs = (IOUserNotificationTestThreadArgs *)arg;

	OSSharedPtr<OSDictionary> dict = OSDictionary::withCapacity(0);
	OSSharedPtr<OSString> rootPath = OSString::withCStringNoCopy(":/");
	dict->setObject(gIOPathMatchKey, rootPath);

	for (size_t i = 0; i < threadArgs->iterations; i++) {
		if (i % 2 == 0) {
			IONotifier * notify = IOService::addMatchingNotification( gIOWillTerminateNotification, dict.get(),
			    &IOUserNotificationMatchingHandler, NULL );
			threadArgs->userNotify->setNotification(notify);
		} else {
			threadArgs->userNotify->setNotification(NULL);
		}
	}

	threadArgs->userNotify->setNotification(NULL);

	IOLockLock(threadArgs->lock);
	*threadArgs->completed = *threadArgs->completed + 1;
	IOLockWakeup(threadArgs->lock, (event_t)threadArgs->completed, true);
	IOLockUnlock(threadArgs->lock);
}

static int
IOUserNotificationTests(__unused int newValue)
{
	constexpr size_t numThreads = 10;
	constexpr size_t numIterations = 500000;
	OSSharedPtr<IOTestUserNotification> userNotify = OSMakeShared<IOTestUserNotification>();
	IOLock * lock = IOLockAlloc();
	size_t threadsCompleted;
	size_t i = 0;
	thread_t threads[numThreads];
	kern_return_t kr;
	bool result;

	struct IOUserNotificationTestThreadArgs threadArgs = {
		.userNotify = userNotify.get(),
		.lock = lock,
		.completed = &threadsCompleted,
		.iterations = numIterations,
	};

	result = userNotify->init();
	assert(result);

	for (i = 0; i < numThreads; i++) {
		kr = kernel_thread_start(&IOUserNotificationTestThread, (void *)&threadArgs, &threads[i]);
		assert(kr == KERN_SUCCESS);
	}

	IOLockLock(lock);
	while (threadsCompleted < numThreads) {
		IOLockSleep(lock, &threadsCompleted, THREAD_UNINT);
		IOLog("%s: Threads completed: %zu/%zu\n", __func__, threadsCompleted, numThreads);
	}
	IOLockUnlock(lock);

	for (i = 0; i < numThreads; i++) {
		thread_deallocate(threads[i]);
	}

	userNotify->setNotification(NULL);

	IOLockFree(lock);

	return KERN_SUCCESS;
}

static void
IOServiceMatchingSharedPtrTests()
{
	OSSharedPtr<const OSSymbol> name = OSSymbol::withCString("name");
	OSSharedPtr<const OSSymbol> value = OSSymbol::withCString("value");

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::serviceMatching("name", table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::serviceMatching("name", table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::serviceMatching(name.get(), table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::serviceMatching(name.get(), table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::nameMatching("name", table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::nameMatching("name", table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::nameMatching(name.get(), table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::nameMatching(name.get(), table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::resourceMatching("name", table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::resourceMatching("name", table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::resourceMatching(name.get(), table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::resourceMatching(name.get(), table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::propertyMatching(name.get(), value.get(), table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::propertyMatching(name.get(), value.get(), table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}

	{
		OSSharedPtr<OSDictionary> table;
		OSSharedPtr<OSDictionary> result = IOService::registryEntryIDMatching(12, table);
		assert(result);
		assert(result->getRetainCount() == 1);

		table = result;
		assert(table->getRetainCount() == 2);
		OSSharedPtr<OSDictionary> result2 = IOService::registryEntryIDMatching(12, table);
		assert(result2);
		assert(result2 == table);
		assert(result2->getRetainCount() == 3);
	}
}

static int
OSSharedPtrTests(int)
{
	OSDynamicPtrCastTests();
	OSConstPtrCastTests();
	OSStaticPtrCastTests();
	IOServiceMatchingSharedPtrTests();
	return 0;
}

static int
IOServiceStateNotificationTests(int)
{
	IOService * service = IOService::getSystemStateNotificationService();
	OSSharedPtr<OSString> str = OSString::withCString(kIOSystemStateClamshellKey);
	kern_return_t kr = service->StateNotificationItemCreate(str.get(), NULL);
	assert(kIOReturnSuccess == kr);

	void (^sendClam)(OSBoolean * state) = ^void (OSBoolean * state) {
		OSSharedPtr<OSDictionary> value;
		kern_return_t kr;

		value = OSDictionary::withCapacity(4);
		value->setObject("value", state);
		kr = IOService::getSystemStateNotificationService()->StateNotificationItemSet(str.get(), value.get());
		assert(kIOReturnSuccess == kr);
	};
	sendClam(kOSBooleanTrue);
	IOSleep(100);
	sendClam(kOSBooleanFalse);

	str = OSString::withCString("test");
	OSSharedPtr<OSArray> array = OSArray::withCapacity(4);
	array->setObject(str.get());
	IOStateNotificationListenerRef listenerRef;
	kr = service->stateNotificationListenerAdd(array.get(), &listenerRef, ^kern_return_t () {
		IOLog("test handler\n");
		kern_return_t kr;
		OSDictionary * dict;
		kr = service->StateNotificationItemCopy(str.get(), &dict);
		if (kIOReturnSuccess == kr) {
		        OSSharedPtr<OSSerialize> s = OSSerialize::withCapacity(4096);
		        dict->serialize(s.get());
		        IOLog("test handler %s\n", s->text());
		}
		return kIOReturnSuccess;
	});
	assert(kIOReturnSuccess == kr);

	OSSharedPtr<IOEventSource> es =
	    IOServiceStateNotificationEventSource::serviceStateNotificationEventSource(
		service, array.get(),
		^void () {
		IOLog("test es handler\n");
		kern_return_t kr;
		OSDictionary * dict;
		kr = service->StateNotificationItemCopy(str.get(), &dict);
		if (kIOReturnSuccess == kr) {
		        OSSharedPtr<OSSerialize> s = OSSerialize::withCapacity(4096);
		        dict->serialize(s.get());
		        IOLog("test es handler %s\n", s->text());
		}
	});
	assert(es);
	IOService::getPlatform()->getWorkLoop()->addEventSource(es.get());
	es->enable();
	IOSleep(30 * 1000);
	IOService::getPlatform()->getWorkLoop()->removeEventSource(es.get());

	return kIOReturnSuccess;
}

static int
IOMallocPageableTests(int)
{
	vm_size_t size = 0;
	vm_size_t alignment = 0;

	for (size = 0; size <= 4 * page_size; size += 64) {
		for (alignment = 1; alignment <= page_size; alignment <<= 1) {
			uintptr_t alignMask = alignment - 1;
			void * addr = IOMallocPageable(size, alignment);
			if (addr == NULL) {
				IOLog("IOMallocPageable(size=%u, alignment=%u) failed\n", (uint32_t)size, (uint32_t)alignment);
				return kIOReturnError;
			}
			if (((uintptr_t)addr & alignMask) != 0) {
				IOLog("IOMallocPageable(size=%u, alignment=%u) returned unaligned pointer %p\n", (uint32_t)size, (uint32_t)alignment, addr);
				return kIOReturnError;
			}
			IOFreePageable(addr, size);

			addr = IOMallocPageableZero(size, alignment);
			if (addr == NULL) {
				IOLog("IOMallocPageableZero(size=%u, alignment=%u) failed\n", (uint32_t)size, (uint32_t)alignment);
				return kIOReturnError;
			}
			if (((uintptr_t)addr & alignMask) != 0) {
				IOLog("IOMallocPageableZero(size=%u, alignment=%u) returned unaligned pointer %p\n", (uint32_t)size, (uint32_t)alignment, addr);
				return kIOReturnError;
			}
			for (char * ptr = (char *)addr; ptr < (char *)addr + size; ptr++) {
				if (*ptr != 0) {
					IOLog("IOMallocPageableZero(size=%u, alignment=%u) -> %p, byte at %p is nonzero\n", (uint32_t)size, (uint32_t)alignment, addr, ptr);
				}
			}
			IOFreePageable(addr, size);
		}
	}

	return kIOReturnSuccess;
}


#endif  /* DEVELOPMENT || DEBUG */

#ifndef __clang_analyzer__
// All the scary things that this function is doing, such as the intentional
// overrelease of an OSData, are hidden from the static analyzer.
static int
sysctl_iokittest(__unused struct sysctl_oid *oidp, __unused void *arg1, __unused int arg2, struct sysctl_req *req)
{
	int error;
	int newValue, changed;

	error = sysctl_io_number(req, 0, sizeof(int), &newValue, &changed);
	if (error) {
		return error;
	}

#if DEVELOPMENT || DEBUG
	if (changed && (66 == newValue)) {
		IOReturn ret;
		OSSharedPtr<IOWorkLoop> wl = IOWorkLoop::workLoop();
		OSSharedPtr<IOCommandGate> cg = IOCommandGate::commandGate(wl.get());
		ret = wl->addEventSource(cg.get());

		struct x {
			uint64_t h;
			uint64_t l;
		};
		struct x y;

		y.h = 0x1111111122222222;
		y.l = 0x3333333344444444;

		kprintf("ret1 %d\n", ret);
		ret = cg->runActionBlock(^(){
			printf("hello %d 0x%qx\n", wl->inGate(), y.h);
			return 99;
		});
		kprintf("ret %d\n", ret);
	}

	if (changed && (999 == newValue)) {
		OSSharedPtr<OSData> data = OSData::withCapacity(16);
		data->release();
	}

	if (changed && (newValue >= 6666) && (newValue <= 6669)) {
		OSSharedPtr<OSIterator> iter;
		IOService  * service;

		service = NULL;
		OSSharedPtr<OSDictionary> matchingDict = IOService::nameMatching("XHC1");
		iter = IOService::getMatchingServices(matchingDict.get());
		if (iter && (service = (IOService *) iter->getNextObject())) {
			if (newValue == 6666) {
				IOLog("terminating 0x%qx\n", service->getRegistryEntryID());
				service->terminate();
			} else if (newValue == 6667) {
				IOLog("register 0x%qx\n", service->getRegistryEntryID());
				service->registerService();
			}
		}
		if (service) {
			return 0;
		}
	}


	if (changed && (555 == newValue)) {
		IOServiceStateNotificationTests(newValue);
	}

	if (changed && newValue) {
		error = IOWorkLoopTest(newValue);
		assert(KERN_SUCCESS == error);
		error = IOServiceTest(newValue);
		assert(KERN_SUCCESS == error);
		error = OSCollectionTest(newValue);
		assert(KERN_SUCCESS == error);
		error = OSCollectionIteratorTests(newValue);
		assert(KERN_SUCCESS == error);
		error = OSAllocationTests(newValue);
		assert(KERN_SUCCESS == error);
		error = OSDataAllocationTests(newValue);
		assert(KERN_SUCCESS == error);
		error = OSBoundedArrayTests(newValue);
		assert(KERN_SUCCESS == error);
		error = OSBoundedArrayRefTests(newValue);
		assert(KERN_SUCCESS == error);
		error = OSBoundedPtrTests(newValue);
		assert(KERN_SUCCESS == error);
		error = OSValueObjectTests(newValue);
		assert(KERN_SUCCESS == error);
		error = IOMemoryDescriptorTest(newValue);
		assert(KERN_SUCCESS == error);
		error = OSSharedPtrTests(newValue);
		assert(KERN_SUCCESS == error);
		error = IOSharedDataQueue_44636964(newValue);
		assert(KERN_SUCCESS == error);
		error = IOUserNotificationTests(newValue);
		assert(KERN_SUCCESS == error);
		error = IOMallocPageableTests(newValue);
		assert(KERN_SUCCESS == error);
	}
#endif  /* DEVELOPMENT || DEBUG */

	return error;
}

SYSCTL_PROC(_kern, OID_AUTO, iokittest,
    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_KERN | CTLFLAG_LOCKED,
    NULL, 0, sysctl_iokittest, "I", "");
#endif // __clang_analyzer__

#if DEVELOPMENT || DEBUG

/*
 * A simple wrapper around an IOService. This terminates the IOService in free().
 */
class TestIOServiceHandle : public OSObject
{
	OSDeclareDefaultStructors(TestIOServiceHandle);
public:
	static TestIOServiceHandle * withService(IOService * service);

private:
	bool initWithService(IOService * service);
	virtual void free() APPLE_KEXT_OVERRIDE;

	IOService * fService;
};

OSDefineMetaClassAndStructors(TestIOServiceHandle, OSObject);

TestIOServiceHandle *
TestIOServiceHandle::withService(IOService * service)
{
	TestIOServiceHandle * handle = new TestIOServiceHandle;
	if (handle && !handle->initWithService(service)) {
		return NULL;
	}
	return handle;
}

bool
TestIOServiceHandle::initWithService(IOService * service)
{
	fService = service;
	fService->retain();
	return true;
}

void
TestIOServiceHandle::free()
{
	if (fService) {
		fService->terminate();
		OSSafeReleaseNULL(fService);
	}
}

/*
 * Set up test IOServices. See the available services in xnu/iokit/Tests/TestServices.
 *
 * xnu darwintests use this sysctl to make these test services available. A send right is pushed
 * to the task that called the sysctl, which when deallocated removes the service. This ensures
 * that the registry isn't polluted by misbehaving tests.
 *
 * Since this sysctl allows callers to instantiate arbitrary classes based on their class name,
 * this can be a security concern. Tests that call this sysctl need the
 * kIOServiceTestServiceManagementEntitlementKey entitlement.
 */
static int
sysctl_iokit_test_service_setup(struct sysctl_oid *oidp, __unused void *arg1, __unused int arg2, struct sysctl_req *req)
{
	char classname[128] = {0};
	IOService * service; // must not release
	OSObject * obj = NULL; // must release
	IOService * provider = NULL; // must not release
	TestIOServiceHandle * handle = NULL; // must release
	mach_port_name_t name __unused;
	int error;

	if (!IOTaskHasEntitlement(current_task(), kIOServiceTestServiceManagementEntitlementKey)) {
		error = EPERM;
		goto finish;
	}

	error = sysctl_handle_string(oidp, classname, sizeof(classname), req);
	if (error != 0) {
		goto finish;
	}

	/*
	 * All test services currently attach to IOResources.
	 */
	provider = IOService::getResourceService();
	if (!provider) {
		IOLog("Failed to find IOResources\n");
		error = ENOENT;
		goto finish;
	}

	obj = OSMetaClass::allocClassWithName(classname);
	if (!obj) {
		IOLog("Failed to alloc class %s\n", classname);
		error = ENOENT;
		goto finish;
	}

	service = OSDynamicCast(IOService, obj);

	if (!service) {
		IOLog("Instance of class %s is not an IOService\n", classname);
		error = EINVAL;
		goto finish;
	}

	if (!service->init()) {
		IOLog("Failed to initialize %s\n", classname);
		error = EINVAL;
		goto finish;
	}

	if (!service->attach(provider)) {
		IOLog("Failed to attach %s\n", classname);
		error = EINVAL;
		goto finish;
	}

	if (!service->start(provider)) {
		IOLog("Failed to start %s\n", classname);
		error = EINVAL;
		goto finish;
	}

	handle = TestIOServiceHandle::withService(service);
	if (!handle) {
		IOLog("Failed to create service handle\n");
		error = ENOMEM;
		goto finish;
	}
	name = iokit_make_send_right(current_task(), handle, IKOT_IOKIT_OBJECT);

	error = 0;

finish:

	OSSafeReleaseNULL(obj);
	OSSafeReleaseNULL(handle);
	return error;
}


SYSCTL_PROC(_kern, OID_AUTO, iokit_test_service_setup,
    CTLTYPE_STRING | CTLFLAG_WR | CTLFLAG_KERN | CTLFLAG_LOCKED,
    NULL, 0, sysctl_iokit_test_service_setup, "-", "");

#endif /* DEVELOPMENT || DEBUG */


static __unused void
CastCompileTest(OSObject *obj)
{
	IOService * service1 = OSDynamicCast(IOService, obj);
	if (service1) {
		service1->terminate();
	}
	IOService *service2 = OSRequiredCast(IOService, obj);
	if (service2) {
		service2->terminate();
	}
}
