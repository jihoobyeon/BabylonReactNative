#import "BabylonNativeInterop.h"

#import <React/RCTViewManager.h>
#import <React/RCTUIManager.h>
#import <ReactCommon/CallInvoker.h>

#import <Foundation/Foundation.h>
#import <MetalKit/MetalKit.h>

@interface EngineView : MTKView

@property (nonatomic, copy) RCTDirectEventBlock onSnapshotDataReturned;
@property (nonatomic, assign) BOOL isTransparent;
@property (nonatomic, assign) NSNumber* antiAliasing;

@end

@implementation EngineView {
    const RCTBridge* bridge;
    MTKView* xrView;
}

- (instancetype)init:(RCTBridge*)_bridge {
    if (self = [super initWithFrame:CGRectZero device:MTLCreateSystemDefaultDevice()]) {
        bridge = _bridge;
        super.translatesAutoresizingMaskIntoConstraints = false;
        super.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
        super.depthStencilPixelFormat = MTLPixelFormatDepth32Float;
    }
    return self;
}

- (void)setIsTransparentFlag:(NSNumber*)isTransparentFlag {
    BOOL isTransparent = [isTransparentFlag intValue] == 1;
    self.isTransparent = isTransparent;
}

- (void)setMSAA:(NSNumber*)value {
    [BabylonNativeInterop updateMSAA:value];
}

- (void)setBounds:(CGRect)bounds {
    [super setBounds:bounds];
    [BabylonNativeInterop updateView:self];
}

- (void)drawRect:(CGRect)rect {
    [BabylonNativeInterop renderView];
}

-(void)dealloc {}

- (void)takeSnapshot {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSBitmapImageRep *bitmapRep = [self bitmapImageRepForCachingDisplayInRect:self.bounds];
        [self cacheDisplayInRect:self.bounds toBitmapImageRep:bitmapRep];

        NSData *jpgData = [bitmapRep representationUsingType:NSBitmapImageFileTypeJPEG properties:@{NSImageCompressionFactor:@(0.8)}];
        NSString *encodedData = [jpgData base64EncodedStringWithOptions:0];

        if (self.onSnapshotDataReturned != nil) {
            self.onSnapshotDataReturned(@{ @"data":encodedData });
        }
    });
}

@end


@interface EngineViewManager : RCTViewManager
@end

@implementation EngineViewManager

RCT_CUSTOM_VIEW_PROPERTY(isTransparent, NSNumber*, EngineView){
    [view setIsTransparentFlag:json];
}

RCT_CUSTOM_VIEW_PROPERTY(antiAliasing, NSNumber*, EngineView){
    [view setMSAA:json];
}

RCT_EXPORT_MODULE(EngineViewManager)

RCT_EXPORT_VIEW_PROPERTY(onSnapshotDataReturned, RCTDirectEventBlock)

RCT_EXPORT_METHOD(takeSnapshot:(nonnull NSNumber*) reactTag) {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSView* view = [self.bridge.uiManager viewForReactTag:reactTag];
        if (!view || ![view isKindOfClass:[EngineView class]]) {
            return;
        }
        [(EngineView*)view takeSnapshot];
    });
}

- (NSView*)view {
    return [[EngineView alloc] init:self.bridge];
}

@end
