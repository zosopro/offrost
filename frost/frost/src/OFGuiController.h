#import "GLee.h"

#import <Cocoa/Cocoa.h>
#include "testApp.h"
#include "CustomGLView.h"
#include "Plugin.h"
#include "PluginIncludes.h"

#include "FrostGuiObjects.h"

@interface ofPlugin : NSObject 
{
	NSString * name;
	NSNumber * enabled;
	NSNumber * header;
	
	FrostPlugin * plugin;
	
}
@property (retain, readwrite) NSString *name;
@property (retain, readwrite) NSNumber *enabled;
@property (retain, readwrite) NSNumber *header;
@property (assign, readwrite) NSNumber *settingsViewNumber;
@property (assign, readwrite) FrostPlugin * plugin;



@end


@interface ListView : NSTableView
{
}
- (void)drawRect:(NSRect)rect;
- (void)drawRow:(NSInteger)rowIndex clipRect:(NSRect)clipRect;
@end


@interface contentView : NSView
{
}
- (void)drawRect:(NSRect)rect;
@end




@interface OFGuiController : NSObject {
@public
	
	testApp * ofApp;
	
	IBOutlet NSView * mainView;	
	IBOutlet contentView * contentArea;
	IBOutlet ListView * listView;
	
	NSMutableArray * viewItems;
	NSMutableArray * views;
	
	NSUserDefaults * userDefaults;
	
	IBOutlet NSTextField * midiStatusText;
	
#pragma mark Plugin View Outlets
	
	IBOutlet NSView *cameraView;
	IBOutlet NSView *blobTrackingView;
	IBOutlet NSView *projectionSurfacesView;
	IBOutlet NSView *cameraKeystoneView;
	
#pragma mark Moon Dust Outlets
	
	IBOutlet NSView *moonDustView;
	
	IBOutlet frostSlider * MoonDustForce;
	IBOutlet frostSlider * MoonDustLength;
	IBOutlet frostSlider * MoonDustDensity;	
	IBOutlet frostSlider * MoonDustSize;
	IBOutlet NSButton * MoonDustDebug;
	IBOutlet frostSlider * MoonDustMasterAlpha;
	IBOutlet frostSlider * MoonDustColumnAlpha;	
	IBOutlet frostSlider * MoonDustColumnMaskAlpha;	
	
#pragma mark La Linea Outlets
	
	IBOutlet NSView *laLineaView;
	IBOutlet NSButton * LaLineaDebug;
	IBOutlet NSButton * LaLineaLockOffsetSliders;
	IBOutlet NSButton * LaLineaLockOffsetSlidersMovie;
	IBOutlet frostSlider * LaLineaMasterAlpha;
	IBOutlet frostCheckbox *LaLineaUseFilm;
	IBOutlet frostSlider *LaLineaDancer;
	IBOutlet frostSlider *LaLineaNoise1;
	IBOutlet frostSlider *LaLineaNoise2;	
	IBOutlet frostSlider *LaLineaNoise3;
	IBOutlet frostCheckbox * LaLineaTrackingActive;
	
#pragma mark La Linea Floor Outlets
	
	IBOutlet frostSlider * LaLineaFloorMasterAlpha;
	IBOutlet NSView *laLineaFloorView;
	IBOutlet frostSlider * LaLineaFloorSpeed;
	IBOutlet frostSlider * LaLineaFloorWidth;	
	IBOutlet frostSlider * LaLineaFloorDirSpeed;
	IBOutlet frostSlider * LaLineaFloorCurl;
	IBOutlet frostSlider * LaLineaMaskAlpha;
	
	IBOutlet NSButton * LaLineaFloorReset;
	
#pragma mark Blob Light Outlets
	
	IBOutlet NSView *blobLightView;
	IBOutlet frostCheckbox * BlobLightDebug;
	IBOutlet frostSlider * BlobLightBlur;
	IBOutlet frostSlider * BlobLightThreshold;
	IBOutlet frostSlider * BlobLightBlur2;
	IBOutlet frostSlider * BlobLightAlpha;
	IBOutlet frostSlider * BlobLightBeta;
	
	IBOutlet frostSlider * BlobLightHistoryAlpha;
	IBOutlet frostSlider * BlobLightBlobAlpha;
	IBOutlet frostSlider * BlobLightAddBackground;
	
	IBOutlet NSColorWell * BlobLightColor;
	IBOutlet NSColorWell * BlobLightHistoryColor;
	
#pragma mark Blob History outlets
	
	IBOutlet NSView *BlobHistoryView;
	IBOutlet frostCheckbox *BlobHistoryIsRecording;
	IBOutlet frostCheckbox *BlobHistoryClearHistory;
	IBOutlet frostCheckbox *BlobHistoryAddPrint;
	IBOutlet frostCheckbox *BlobHistoryRemovePrint;
	IBOutlet frostCheckbox *BlobHistoryRemoveAllPrints;
	IBOutlet frostCheckbox *BlobHistoryClearIce;
	IBOutlet frostCheckbox *BlobHistoryFill;
	
	IBOutlet frostCheckbox *BlobHistoryClearFreeze;
	
	IBOutlet frostSlider *BlobHistoryMasterAlpha;
	
	IBOutlet frostSlider *BlobHistoryPlayDirection;
	IBOutlet frostSlider *BlobHistoryAlpha;
	IBOutlet frostSlider *BlobHistoryPrintsAlpha;
	
	IBOutlet frostSlider * BlobHistoryGrow;
	IBOutlet frostSlider * BlobHistoryDecrease;
	IBOutlet frostSlider * BlobHistoryFreezeSpeed;
	IBOutlet frostSlider * BlobHistoryFreezeStrength;
	
#pragma mark Spotlight outlets
	
	IBOutlet NSView *SpotlightView;
	IBOutlet frostSlider * SpotlightMasterAlpha;
	IBOutlet frostSlider * SpotlightRadiusMultiplier;
	
#pragma mark MirrorBall outlets
	
	IBOutlet NSView *MirrorBallView;
	
	IBOutlet frostSlider * MirrorBallMasterAlpha;
	
	IBOutlet frostCheckbox * MirrorBallReflection1DotAdd;
	IBOutlet frostCheckbox * MirrorBallReflection1DotRemove;
	IBOutlet frostCheckbox * MirrorBallReflection1Clear;
	
	IBOutlet frostSlider * MirrorBallReflection1OnFraction;
	IBOutlet frostSlider * MirrorBallReflection1AlphaFraction;
	IBOutlet frostSlider * MirrorBallReflection1DotSize;
	
	IBOutlet frostCheckbox * MirrorBallReflection2DotAdd;
	IBOutlet frostCheckbox * MirrorBallReflection2DotRemove;
	IBOutlet frostCheckbox * MirrorBallReflection2Clear;
	IBOutlet frostSlider * MirrorBallReflection2DotSize;
	
	IBOutlet frostSlider * MirrorBallReflection2OnFraction;
	IBOutlet frostSlider * MirrorBallReflection2AlphaFraction;
	
	IBOutlet frostSlider * MirrorBallRotationFactor;
	
#pragma mark LEDGrid outlets
	
	IBOutlet NSView *LEDGridlView;
	IBOutlet frostSlider * LEDMasterFader;
	IBOutlet frostSlider * LEDRadius;
	IBOutlet NSColorWell * LEDblobColor;
	IBOutlet NSColorWell * LEDbackgroundColor;
	IBOutlet frostCheckbox * LEDdebug;
	IBOutlet frostSlider * LEDPT1X;
	IBOutlet frostSlider * LEDPT1Y;
	IBOutlet frostSlider * LEDPT2X;
	IBOutlet frostSlider * LEDPT2Y;
#pragma mark Folding outlets
	
	IBOutlet NSView *foldingView;
	IBOutlet frostSlider * foldingAlpha;
	IBOutlet frostSlider * foldingHistoryAddMultiplier;
	IBOutlet frostSlider * foldingHistoryAlpha;
	IBOutlet frostSlider * foldingHistoryPush1;
	IBOutlet frostSlider * foldingHistoryPush2;
	IBOutlet frostSlider * foldingHistoryPush3;
	IBOutlet frostSlider * foldingFishAlpha;
	IBOutlet frostSlider * foldingFloorbox;
	IBOutlet frostSlider * foldingFloorboxAlpha;
	IBOutlet frostSlider * foldingOffsetX;
	IBOutlet frostSlider * foldingOffsetY;
	IBOutlet frostSlider * foldingScale;
	IBOutlet frostCheckbox * foldingHistoryClear;
	IBOutlet frostCheckbox * foldingReset;
	IBOutlet frostCheckbox * foldingUpdateHistoryFromBlob;
	
#pragma mark Frostscape outlets
	
	IBOutlet NSView *frostscapeView;
	IBOutlet frostSlider * FrostScapeSlider1;
	IBOutlet frostSlider * FrostScapeSlider2;
	IBOutlet frostSlider * FrostScapeSlider3;
	IBOutlet frostSlider * FrostScapeSlider4;
	IBOutlet frostSlider * FrostScapeSlider5;
	IBOutlet frostSlider * FrostScapeSlider6;
	
	IBOutlet frostSlider * FrostscapeSideFreeze;
	IBOutlet frostSlider * FrostscapeColumnFreeze1;
	IBOutlet frostSlider * FrostscapeColumnFreeze2;
	IBOutlet frostSlider * FrostscapeColumnFreeze3;
	IBOutlet frostSlider * FrostscapeFreezeColumns;
	
	IBOutlet frostSlider * FrostscapeWhiteBackground;
	IBOutlet frostCheckbox * FrostscapeAddLines;
	IBOutlet frostSlider * FrostscapeLinesAlpha;
	
	IBOutlet frostCheckbox * FrostscapeInvert;
	IBOutlet frostSlider * FrostscapeMasterAlpha;
	IBOutlet frostSlider * FrostscapeLinesAddSpeed;
	IBOutlet frostCheckbox * FrostscapeResetLines;
	IBOutlet frostSlider * FrostscapeFreezeLines;
	
	
#pragma mark LiquidSpace outlets
	IBOutlet frostSlider * liquidSpaceMasterAlpha;
	
	IBOutlet NSView *liquidSpaceView;
	IBOutlet frostCheckbox * liquidUpdateMotor;
	IBOutlet frostCheckbox * liquidSpaceFIll;
	IBOutlet NSColorWell * liquidSpaceFillColor;
	IBOutlet frostSlider * liquidSpaceFadeSpeed;
	IBOutlet frostSlider * liquidSpaceViscosity;
	IBOutlet frostSlider * liquidSpaceDiffusion;
	IBOutlet NSColorWell * liquidSpaceDropColor;
	IBOutlet frostCheckbox * liquidSpaceAddingColor;
	IBOutlet frostSlider * liquidSpaceColorMultiplier;
	IBOutlet frostCheckbox * liquidSpaceAddingForce;
	IBOutlet frostSlider * liquidSpaceForceMultiplier;
	IBOutlet frostSlider * liquidSpaceSpeed;
	IBOutlet frostCheckbox * liquidSpaceClear;
	IBOutlet frostCheckbox * liquidSpaceAddRing1;
	IBOutlet frostCheckbox * liquidSpaceAddRing2;
	IBOutlet frostCheckbox * liquidSpaceAddRing3;
	IBOutlet frostCheckbox * liquidSpaceAddFixedRing2;
	IBOutlet frostSlider * liquidSpaceWhiteBlue;
	
#pragma mark Camera Outlets
	
	IBOutlet NSView * cameraSetting;
	
	IBOutlet NSView * cameraSettings1;
	IBOutlet NSView * cameraSettings2;
	IBOutlet NSView * cameraSettings3;
	
	IBOutlet frostSlider * cameraBrightness1;
	IBOutlet frostSlider * cameraBrightness2;
	IBOutlet frostSlider * cameraBrightness3;
	
	IBOutlet frostSlider * cameraGain1;
	IBOutlet frostSlider * cameraGain2;
	IBOutlet frostSlider * cameraGain3;
	
	IBOutlet frostSlider * cameraShutter1;
	IBOutlet frostSlider * cameraShutter2;
	IBOutlet frostSlider * cameraShutter3;
	
	IBOutlet frostSlider * cameraExposure1;
	IBOutlet frostSlider * cameraExposure2;
	IBOutlet frostSlider * cameraExposure3;
	
	IBOutlet frostSlider * cameraGamma1;
	IBOutlet frostSlider * cameraGamma2;
	IBOutlet frostSlider * cameraGamma3;
	
	IBOutlet NSTextField * CameraGUID1;
	IBOutlet NSTextField * CameraGUID2;
	IBOutlet NSTextField * CameraGUID3;
	
#pragma mark Projector Outlets
	
	IBOutlet NSButton * ProjectorShowDebug;
	IBOutlet NSMatrix * ProjectorMatrix;
	IBOutlet NSSlider * ProjectorFloorAspect;
	IBOutlet NSButton * ProjectorLockFloorAspect;
	IBOutlet NSTextField * ProjectorFloorAspectText;
	
#pragma mark Camera Keystone Outlets
	
	IBOutlet frostSlider *LaLineaOffsetX1;
	IBOutlet frostSlider *LaLineaOffsetY1;
	IBOutlet frostSlider *LaLineaOffsetX2;
	IBOutlet frostSlider *LaLineaOffsetY2;
	IBOutlet frostSlider *LaLineaOffsetX1Movie;
	IBOutlet frostSlider *LaLineaOffsetY1Movie;
	IBOutlet frostSlider *LaLineaOffsetX2Movie;
	IBOutlet frostSlider *LaLineaOffsetY2Movie;
	
	
#pragma mark Blob Tracking Outlets
	
	IBOutlet NSSlider * BlobThreshold1;
	IBOutlet NSSlider * BlobBlur1;
	IBOutlet frostCheckbox * BlobActive1;
	IBOutlet NSSlider * BlobThreshold2;
	IBOutlet NSSlider * BlobBlur2;
	IBOutlet frostCheckbox * BlobActive2;
	IBOutlet NSSlider * BlobThreshold3;
	IBOutlet NSSlider * BlobBlur3;
	IBOutlet frostCheckbox * BlobActive3;
	IBOutlet frostCheckbox * Blob1OnlyCurtain;
	IBOutlet NSTextField * TrackingActive1;
	IBOutlet NSTextField * TrackingActive2;
	IBOutlet NSTextField * TrackingActive3;
	
#pragma mark OpenGL Views
	
	IBOutlet CustomGLView * camView;
	IBOutlet CustomGLView * projectorView;
	IBOutlet CustomGLView * cameraKeystoneOpenGlView;
	IBOutlet CustomGLView * blobView;
	IBOutlet CustomGLView * floorPreview;
	
	
}
@property (retain, readwrite) NSMutableArray *viewItems;
@property (retain, readwrite) NSMutableArray *views;

-(IBAction) setListViewRow:(id)sender;


// ------------------------------------------------
- (id)tableView:(NSTableView *)aTableView;

-(IBAction)		toggleFullscreen:(id)sender;

-(void)			setFPS:(float)framesPerSecond;

-(void) changePluginEnabled:(int)n enable:(bool)enable;
-(void) changeView:(int)n;

#pragma mark Camera Actions

-(IBAction)		cameraBindGuid1:(id)sender;
-(IBAction)		cameraBindGuid2:(id)sender;
-(IBAction)		cameraBindGuid3:(id)sender;

#pragma mark MoonDust Actions

-(IBAction)		modifyMoonDustForce:(id)sender;
-(IBAction)		modifyMoonDustLength:(id)sender;
-(IBAction)		modifyMoonDustSize:(id)sender;
-(IBAction)		modifyMoonDustDensity:(id)sender;
-(IBAction)		modifyMoonDustDebug:(id)sender;

#pragma mark La Linea Actions

-(IBAction)		modifyLaLineaDebug:(id)sender;

-(IBAction)		modifyLaLineaFloorWidth:(id)sender;
-(IBAction)		modifyLaLineaFloorSpeed:(id)sender;
-(IBAction)		modifyLaLineaFloorDirSpeed:(id)sender;
-(IBAction)		modifyLaLineaFloorReset:(id)sender;

-(IBAction)		modifyLaLineaLockOffsetSliders:(id)sender;
-(IBAction)		modifyLaLineaUseFilm:(id)sender;
-(IBAction)		modifyLaLineaTrackingActive:(id)sender;

#pragma mark Blob Light Actions

-(IBAction)		modifyBlobLightDebug:(id)sender;
-(IBAction)		modifyBlobLightColor:(id)sender;
-(IBAction)		modifyBlobLightColor2:(id)sender;
-(IBAction)		modifyBlobLightBlur:(id)sender;
-(IBAction)		modifyBlobLightThreshold:(id)sender;
-(IBAction)		modifyBlobLightBlur2:(id)sender;
-(IBAction)		modifyBlobLightAlpha:(id)sender;
-(IBAction)		modifyBlobLightBeta:(id)sender;
-(IBAction)		modifyBlobLightHistoryAlpha:(id)sender;
-(IBAction)		modifyBlobLightBlobAlpha:(id)sender;
-(IBAction)		modifyBlobLightBackgroundAdd:(id)sender;
-(IBAction)		modifyBlobLightBackgroundClear:(id)sender;

#pragma mark Frostscape Actions

-(IBAction)		modifyFrostscapeSlider1:(id)sender;
-(IBAction)		modifyFrostscapeSlider2:(id)sender;
-(IBAction)		modifyFrostscapeSlider3:(id)sender;
-(IBAction)		modifyFrostscapeSlider4:(id)sender;
-(IBAction)		modifyFrostscapeSlider5:(id)sender;
-(IBAction)		modifyFrostscapeSlider6:(id)sender;
-(IBAction)		frostscapeFillIce:(id)sender;
-(IBAction)		frostscapeEmptyIce:(id)sender;

#pragma mark Folding Actions

-(IBAction)		modifyFoldingHistoryAddMultiplier:(id)sender;

#pragma mark LiquidSpace Actions

-(IBAction)		liquidAddRing1:(id)sender;
-(IBAction)		liquidAddRing2:(id)sender;
-(IBAction)		liquidAddRing3:(id)sender;

-(IBAction)		liquidAddFixedRing2:(id)sender;

-(IBAction)		modifyLiquidSpaceFillColor:(id)sender;
-(IBAction)		modifylLiquidSpace:(id)sender;
-(IBAction)		modifyLiquidSpaceFadeSpeed:(id)sender;
-(IBAction)		modifyLiquidSpaceViscosity:(id)sender;
-(IBAction)		modifyLiquidSpaceDiffusion:(id)sender;
-(IBAction)		modifyLiquidSpaceDropColor:(id)sender;
-(IBAction)		modifyLiquidSpaceAddingColor:(id)sender;
-(IBAction)		modifyLiquidSpaceColorMultiplier:(id)sender;
-(IBAction)		modifyLiquidSpaceAddingForce:(id)sender;
-(IBAction)		modifyLiquidSpaceForceMultiplier:(id)sender;
-(IBAction)		modifyLiquidSpaceWhiteBlue:(id)sender;

#pragma mark Projector Surfaces Actions

-(IBAction)		modifyProjectorShowDebug:(id)sender;
-(IBAction)		modifyProjectorMatrix:(id)sender;
-(IBAction)		modifyProjectorFloorAspect:(id)sender;
-(IBAction)		modifyProjectorLockFloorAspect:(id)sender;


#pragma mark Camera Keystone Actions

-(IBAction)		modifyCameraKeystoneShowDebug:(id)sender;
-(IBAction)		modifyCameraKeystoneMatrix:(id)sender;

#pragma mark Blob Tracker Actions

-(IBAction)		modifyBlobThreshold1:(id)sender;
-(IBAction)		modifyBlobBlur1:(id)sender;
-(IBAction)		blobGrab1:(id)sender;
-(IBAction)		modifyBlobActive1:(id)sender;
-(IBAction)		modifyBlobThreshold2:(id)sender;
-(IBAction)		modifyBlobBlur2:(id)sender;
-(IBAction)		blobGrab2:(id)sender;
-(IBAction)		modifyBlobActive2:(id)sender;
-(IBAction)		modifyBlobThreshold3:(id)sender;
-(IBAction)		modifyBlobBlur3:(id)sender;
-(IBAction)		blobGrab3:(id)sender;
-(IBAction)		modifyBlobActive3:(id)sender;
-(IBAction)		drawBlobDebug:(id)sender;

#pragma mark Blob History Actions

-(IBAction) modifyBlobHistoryIsRecording:(id)sender;
-(IBAction) modifyBlobHistoryClearHistory:(id)sender;
-(IBAction) modifyBlobHistoryAddSnapshot:(id)sender;
-(IBAction) modifyBlobHistoryRemoveSnapshot:(id)sender;
-(IBAction) modifyBlobHistoryClearSnapshots:(id)sender;

#pragma mark MirrorBall Actions

-(IBAction) modifyMirrorBall1AddReflection:(id)sender;
-(IBAction) modifyMirrorBall1RemoveReflection:(id)sender;
-(IBAction) modifyMirrorBall1ClearReflections:(id)sender;

-(IBAction) modifyMirrorBall2AddReflection:(id)sender;
-(IBAction) modifyMirrorBall2RemoveReflection:(id)sender;
-(IBAction) modifyMirrorBall2ClearReflections:(id)sender;

-(IBAction) ledSetBlobColor:(id)sender;
-(IBAction) ledSetBackgroundColor:(id)sender;
# pragma mark Callbacks

-(void)			awakeFromNib;
-(void)			cameraUpdateGUIDs;

-(id)			init;


@end



extern OFGuiController * gui;