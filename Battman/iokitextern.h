//
//  iokitextern.h
//  Battman
//
//  Created by Torrekie on 2025/5/20.
//

#ifndef iokitextern_h
#define iokitextern_h

#include <CoreFoundation/CoreFoundation.h>
#include <dispatch/dispatch.h>

#if __has_include(<IOKit/IOKitLib.h>)
#include <IOKit/IOKitLib.h>
#else
#if __has_include(<mach/mach.h>)
#include <mach/mach.h>
#else
__BEGIN_DECLS
typedef __darwin_mach_port_t mach_port_t;
typedef struct task *task_t;
typedef task_t task_port_t;
__END_DECLS
#endif

__BEGIN_DECLS

extern const mach_port_t kIOMasterPortDefault;

typedef mach_port_t io_object_t;

typedef io_object_t io_iterator_t;
typedef io_object_t io_service_t;
typedef io_object_t io_connect_t;
typedef io_object_t io_registry_entry_t;
typedef int IOReturn;
typedef int kern_return_t;
#define kIOReturnSuccess 0
#define kIOReturnError 0xE00002BC
#define MACH_PORT_NULL 0
#define IO_OBJECT_NULL  ((io_object_t) 0)

typedef struct IONotificationPort *IONotificationPortRef;

typedef void (*IOServiceInterestCallback)(void *refcon, io_service_t service, uint32_t messageType, void *messageArgument);
typedef void (*IOServiceMatchingCallback)(void *refcon, io_iterator_t iterator);

extern IOReturn IOMasterPort(mach_port_t, mach_port_t *);
extern int IOServiceAddMatchingNotification(void *, const char *, void *, void *, void *, io_iterator_t *);
extern CFMutableDictionaryRef IOServiceMatching(const char *);
extern kern_return_t IOServiceOpen(io_service_t, task_port_t, uint32_t, io_connect_t *);
extern io_service_t IOServiceGetMatchingService(mach_port_t, CFDictionaryRef);
extern int IOServiceAddInterestNotification(IONotificationPortRef, io_service_t, const char *, void *, int, void *);
extern int IORegistryEntryCreateCFProperties(io_registry_entry_t, CFMutableDictionaryRef *, CFAllocatorRef, uint32_t);
extern kern_return_t IOConnectCallStructMethod(mach_port_t, uint32_t, const void *, size_t, void *, size_t *);
extern kern_return_t IOServiceClose(io_connect_t);
extern io_object_t IOIteratorNext(io_iterator_t);
extern kern_return_t IOObjectRelease(io_object_t);
extern IONotificationPortRef IONotificationPortCreate(mach_port_t);
extern void IONotificationPortSetDispatchQueue(IONotificationPortRef, dispatch_queue_t);
extern kern_return_t IOServiceGetMatchingServices(mach_port_t masterPort, CFDictionaryRef matching, io_iterator_t *existing);
extern CFTypeRef IORegistryEntryCreateCFProperty(io_registry_entry_t, CFStringRef, CFAllocatorRef, uint32_t);
__END_DECLS
#endif

#endif /* iokitextern_h */
