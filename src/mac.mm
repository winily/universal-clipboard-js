#import <AppKit/AppKit.h>
#import <CoreServices/CoreServices.h>
#import <Foundation/Foundation.h>
#import <objc/objc-runtime.h>

#include "mac.h"

Napi::Value Read_Impl(std::string format, Napi::Env env) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  NSString *dataType = [NSString stringWithUTF8String:format.c_str()];
  NSData *data = [NSPasteboard.generalPasteboard dataForType:dataType];
  uint8_t *pbData = (uint8_t *)data.bytes;
  uint32_t len = (uint32_t)data.length;
  Napi::Buffer<uint8_t> buffer = Napi::Buffer<uint8_t>::Copy(env, pbData, len);
  [pool drain];
  return buffer;
}

Napi::Value Clear_Impl(Napi::Env env) {
  [NSPasteboard.generalPasteboard clearContents];
  return env.Undefined();
}

Napi::Value Write_Impl(std::string format_str, Napi::Buffer<uint8_t> buffer,
                      Napi::Env env) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  // arg1: format
  NSString *format = [NSString stringWithUTF8String:format_str.c_str()];

  // arg2: buffer
  uint8_t *buf = buffer.Data();
  size_t length = buffer.Length();

  // copy
  NSData *data = [NSData dataWithBytes:buf length:(NSUInteger)length];
  // format
  [NSPasteboard.generalPasteboard declareTypes:@[ format ] owner:nil];
  // setData
  BOOL success = [NSPasteboard.generalPasteboard setData:data forType:format];
  [pool drain];
  return Napi::Boolean::New(env, success);
}