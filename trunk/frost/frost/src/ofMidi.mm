//
//  ofMidi.m
//  openFrameworks
//
//  Created by Jonas Jongejan on 02/10/09.
//  Copyright 2009 HalfdanJ. All rights reserved.
//

#import "ofMidi.h"


@implementation ofMidi
-(void) awakeFromNib{
	printf("\n\n\n&&&&&&& MIDI WAKE UP &&&&&&&\n");
	
	manager = [PYMIDIManager sharedInstance];
	endpoint = new PYMIDIRealEndpoint;
    NSArray* endpointArray = [manager realSources];
    
    NSEnumerator* enumerator = [endpointArray objectEnumerator];
	endpoint = [endpointArray objectAtIndex:1];
	NSLog([endpoint displayName]);
	printf("Is it in use? %d\n",[endpoint isInUse]);
	[endpoint addReceiver:self];
	
	frostSliderHookups  = [[NSMutableArray alloc] initWithCapacity:10];
	
	[self hookupSlider:gui->MoonDustMasterAlpha onChannel:4 onNumber:1 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->MoonDustForce onChannel:4 onNumber:2 controlChanges:true noteChanges:false scale:3.0/127.0];
	[self hookupSlider:gui->MoonDustLength onChannel:4 onNumber:3 controlChanges:true noteChanges:false scale:3000.0/127.0];
	[self hookupSlider:gui->MoonDustDensity onChannel:4 onNumber:4 controlChanges:true noteChanges:false scale:10000.0/127.0];
	[self hookupSlider:gui->MoonDustSize onChannel:4 onNumber:5 controlChanges:true noteChanges:false scale:0.1/127.0];
	[self hookupSlider:gui->MoonDustColumnAlpha onChannel:4 onNumber:6 controlChanges:true noteChanges:false scale:1.0/127.0];
	
	[self hookupSlider:gui->foldingHistoryAddMultiplier onChannel:8 onNumber:2 controlChanges:true noteChanges:false scale:1.0/127.0];
	
	
	[self hookupSlider:gui->FrostscapeMasterAlpha onChannel:9 onNumber:1 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostScapeSlider1 onChannel:9 onNumber:2 controlChanges:true noteChanges:false scale:10.0/127.0];
	[self hookupSlider:gui->FrostScapeSlider2 onChannel:9 onNumber:3 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostScapeSlider3 onChannel:9 onNumber:4 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostScapeSlider5 onChannel:9 onNumber:5 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostScapeSlider6 onChannel:9 onNumber:6 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostscapeSideFreeze onChannel:9 onNumber:7 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostscapeColumnFreeze onChannel:9 onNumber:8 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->FrostScapeSlider4 onChannel:9 onNumber:9 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupButton:gui->FrostscapeInvert onChannel:9 onNumber:12 controlChanges:true noteChanges:false];
	[self hookupSlider:gui->FrostscapeWhiteBackground onChannel:9 onNumber:13 controlChanges:true noteChanges:false scale:1.0/127.0];
	
	[self hookupSlider:gui->LaLineaMasterAlpha onChannel:5 onNumber:1 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->LaLineaFloorMasterAlpha onChannel:5 onNumber:1 controlChanges:true noteChanges:false scale:1.0/127.0];
	
	[self hookupSlider:gui->LaLineaFloorSpeed onChannel:6 onNumber:2 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->LaLineaFloorDirSpeed onChannel:6 onNumber:3 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->LaLineaFloorWidth onChannel:6 onNumber:4 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->LaLineaFloorCurl onChannel:6 onNumber:5 controlChanges:true noteChanges:false scale:1.0/127.0];
	[self hookupSlider:gui->LaLineaMaskAlpha onChannel:6 onNumber:6 controlChanges:true noteChanges:false scale:1.0/127.0];
	
	// set gui info for booleans
	
	[gui->BlobActive1 setMidiChannel:1 number:1 control:true note:false];
	[gui->BlobActive2 setMidiChannel:1 number:2 control:true note:false];
	[gui->BlobActive3 setMidiChannel:1 number:3 control:true note:false];
	
	[gui->LaLineaTrackingActive setMidiChannel:5 number:2 control:true note:false];
	[gui->LaLineaUseFilm setMidiChannel:5 number:3 control:true note:false];
	
	
	
}
-(void) hookupSlider:(frostSlider*)slider onChannel:(int)channel onNumber:(int)number controlChanges:(bool)control noteChanges:(bool)note scale:(float)scale{
	[frostSliderHookups addObject:slider];
	
	[slider setMidiChannel:channel number:number control:control note:note scale:scale];
}

-(void) hookupButton:(frostCheckbox*)slider onChannel:(int)channel onNumber:(int)number controlChanges:(bool)control noteChanges:(bool)note {
	[frostSliderHookups addObject:slider];
	[slider setMidiChannel:channel number:number control:control note:note];
}
- (void)processMIDIPacketList:(MIDIPacketList*)packetList sender:(id)sender
{
	MIDIPacket *packet = &packetList->packet[0];
	for (int i = 0; i < packetList->numPackets; ++i) {
		printf("Midi: %i\n",packet->data[0]);
		bool noteOn = false;
		bool noteOff = false;
		bool controlChange;
		int channel = -1;
		int number = -1;
		int value = -1;
		
		if(packet->data[0] >= 144 && packet->data[0] <= 159){
			noteOn = true;
			channel = packet->data[0] - 143;
			number = packet->data[1];
			value = packet->data[2];
		}
		if(packet->data[0] >= 128 && packet->data[0] <= 143){
			noteOff = true;
			channel = packet->data[0] - 127;
			number = packet->data[1];
			value = packet->data[2];
		}
		if(packet->data[0] >= 176 && packet->data[0] <= 191){
			controlChange = true;
			channel = packet->data[0] - 175;
			number = packet->data[1];
			value = packet->data[2];
		}
		if([midiActive state] ==  NSOnState){
			for(int i=0;i<[frostSliderHookups count];i++){
				[[frostSliderHookups objectAtIndex:i] receiveMidiOnChannel:channel number:number control:controlChange noteOn:noteOn noteOff:noteOff value:value];
			}
			
			//packet = MIDIPacketNext(packet);
			if(controlChange && number == 0){
				//[gui changePluginEnabled:channel enable:(value ==0)?false:true];
			}	
			
			//Blob tracker
			if(controlChange && channel == 1){
				if(number == 1){
					if(value == 0){
						[gui->BlobActive1 setState:NSOffState];
					}
					if(value > 0){
						[gui->BlobActive1 setState:NSOnState];
					}
					[gui modifyBlobActive1:gui->BlobActive1];
					
				}
				
				if(number == 2){
					if(value == 0){
						[gui->BlobActive2 setState:NSOffState];
					}
					if(value > 0){
						[gui->BlobActive2 setState:NSOnState];
					}
					[gui modifyBlobActive2:gui->BlobActive2];
				}
				
				if(number == 3){
					if(value == 0){
						[gui->BlobActive3 setState:NSOffState];
					}
					if(value > 0){
						[gui->BlobActive3 setState:NSOnState];
					}
					[gui modifyBlobActive3:gui->BlobActive3];
				}
				
				if(number == 4){
					printf("Grab %i",value);
					if(value == 0){
						[gui blobGrab1:self];
					}
					if(value == 1){
						[gui blobGrab2:self];
					}
					if(value == 2){
						[gui blobGrab3:self];
					}
				}
			}
			
			if(controlChange && channel == 5){
				if(number == 2){
					if(value == 0){
						[gui->LaLineaTrackingActive setState:NSOffState];
					}
					if(value > 0){
						[gui->LaLineaTrackingActive setState:NSOnState];
					}
					[gui modifyLaLineaTrackingActive:gui->LaLineaTrackingActive];
					
				}
				if(number == 3){
					if(value == 0){
						[gui->LaLineaUseFilm setState:NSOffState];
					}
					if(value > 0){
						[gui->LaLineaUseFilm setState:NSOnState];
					}
					[gui modifyLaLineaUseFilm:gui->LaLineaUseFilm];
					
				}
			}
			
			//LaLineaFloor
			if(controlChange && channel == 6){
				if(number == 6){
					[gui modifyLaLineaFloorReset:self];
				}
			}
			
			//Frostscape
			if(controlChange && channel == 9){
				if(number == 10 && value > 0){
					[gui frostscapeEmptyIce:self];
					cout<<"EMPTY ICE"<<endl;
				}
				
				if(number == 11 && value > 0){
					[gui frostscapeFillIce:self];
				}
			}
			
			
			
		}
		
		packet = &packetList->packet[i];
	}	
}
@end