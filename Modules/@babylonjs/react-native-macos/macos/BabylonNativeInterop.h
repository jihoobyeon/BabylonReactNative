#pragma once

#import <MetalKit/MetalKit.h>
#import <React/RCTBridge.h>

@interface BabylonNativeInterop : NSObject
+ (void)initialize:(RCTBridge*)bridge;
+ (void)updateView:(MTKView*)mtkView;
+ (void)updateMSAA:(NSNumber*)value;
+ (void)renderView;
+ (void)resetView;
@end
