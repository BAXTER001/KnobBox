#include <HID-Project.h>
#include <HID-Settings.h>

#include <Encoder.h>
#include <AceButton.h>
using namespace ace_button;




Encoder   knobLeft(18,19);
AceButton buttLeft(20);
int  leftDown = 0;
int  leftClick = 0;
int  leftDblClick = 0;
int  leftLongPress = 0;
long positionLeft = -999;
long newLeft;

Encoder   knobMid(14,15);
AceButton buttMid(16);
int  midDown = 0;
int  midClick = 0;
int  midDblClick = 0;
int  midLongPress = 0;
long positionMid = -999;
long newMid;

Encoder   knobRight(4,2);
AceButton buttRight(7);
int  rightDown = 0;
int  rightClick = 0;
int  rightDblClick = 0;
int  rightLongPress = 0;
long positionRight = -999;
long newRight;




unsigned long debounceDelay = 120; 
unsigned long lastDebounceTime = 0; 
unsigned long lastColorUpdate = millis();


void handleButtonEvent(AceButton* button, uint8_t eventType, uint8_t ) {
  uint8_t id = button->getId();
  switch (eventType) {


      case AceButton::kEventPressed:
        if(id == 0){leftDown=1;}
        else if(id == 1){midDown=1;}
        else if(id == 2){rightDown=1;}
        break;
      case AceButton::kEventReleased:
        if(id == 0){leftDown=0;}
        else if(id == 1){midDown=0;}
        else if(id == 2){rightDown=0;}
        break;
      case AceButton::kEventRepeatPressed:
        if(id == 0){leftClick=1;}
        else if(id == 1){midClick=1;}
        else if(id == 2){rightClick=1;}
        break;
     case AceButton::kEventClicked:
        if(id == 0){leftClick=1;}
        else if(id == 1){midClick=1;}
        else if(id == 2){rightClick=1;}
        break;
     case AceButton::kEventDoubleClicked:
        if(id == 0){leftDblClick=1;}
        else if(id == 1){midDblClick=1;}
        else if(id == 2){rightDblClick=1;}
        break;
     case AceButton::kEventLongPressed:
        if(id == 0){leftLongPress=1;}
        else if(id == 1){midLongPress=1;}
        else if(id == 2){rightLongPress=1;}
        break;
 
  }
}


void setup() {

  analogWrite(9, 255-(0/50) );
  analogWrite(6, 255-(0/50) );
  analogWrite(5, 255-(0/50) );

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  
  analogWrite(9, 255-(0/50) );
  analogWrite(6, 255-(0/50) );
  analogWrite(5, 255-(0/50) );


  ButtonConfig* buttonLeftConfig = buttLeft.getButtonConfig();
  buttonLeftConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonLeftConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonLeftConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonLeftConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);  
  buttonLeftConfig->setFeature(ButtonConfig::kFeatureSuppressAfterRepeatPress);
  buttonLeftConfig->setEventHandler(handleButtonEvent);

  ButtonConfig* buttonMidConfig = buttMid.getButtonConfig();
  buttonMidConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonMidConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonMidConfig->setFeature(ButtonConfig::kFeatureLongPress); 
  buttonMidConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);  
  buttonMidConfig->setEventHandler(handleButtonEvent);
  
  ButtonConfig* buttonRightConfig = buttRight.getButtonConfig();
  buttonRightConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonRightConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonRightConfig->setFeature(ButtonConfig::kFeatureLongPress); 
  buttonRightConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);  
  

  buttonRightConfig->setEventHandler(handleButtonEvent);

  pinMode(20, INPUT_PULLUP);
  buttLeft.init(20, HIGH, 0 );

  pinMode(16, INPUT_PULLUP);
  buttMid.init(16,  HIGH, 1 );

  pinMode(7, INPUT_PULLUP);
  buttRight.init(7, HIGH, 2 );
  
  Keyboard.begin();
  Consumer.begin(); 
  lastColorUpdate = millis();
}

struct KeyCodeDef
{
    KeyboardKeycode keycode;
    ConsumerKeycode consumerKeycode;
    bool            skipDebounce;
    KeyboardKeycode modifier;
};

struct KnobKeyMapDef{
  KeyCodeDef onClick;
  KeyCodeDef onDblClick;
  KeyCodeDef onReleasedClockwise;
  KeyCodeDef onReleasedAntiClockwise;
  KeyCodeDef onPressedClockwise;
  KeyCodeDef onPressedAntiClockwise;
  KeyCodeDef onLongPress;
};

struct KnobLayerDef{
  KnobKeyMapDef left;
  KnobKeyMapDef mid;
  KnobKeyMapDef right;
  int red;
  int green;
  int blue;
};

KnobLayerDef keyMaps[] = {

  {/*-- WHITE LAYER --*/
    .left   = { .onClick={                  .keycode=KEY_M,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onDblClick={               .keycode=KEY_Q,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                        
                .onReleasedClockwise={      .keycode=KEY_UP_ARROW,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onReleasedAntiClockwise={  .keycode=KEY_DOWN_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RIGHT_ARROW, .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_LEFT_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_D,           .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_LEFT_GUI}, 
              },
                 
    .mid    = { .onClick={                  .keycode=KEY_SPACE,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                                       
                .onDblClick={               .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedClockwise={      .keycode=KEY_Y,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedAntiClockwise={  .keycode=KEY_U,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL}, 
              },
    
    .right  = { .onClick={                  .keycode=KEY_TAB,         .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL},  
                .onDblClick={               .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
                .onReleasedClockwise={      .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_UP,         .skipDebounce=1,  .modifier=KEY_RESERVED},           
                .onReleasedAntiClockwise={  .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_DOWN,       .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_NEXT,              .skipDebounce=0,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_PREVIOUS,          .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
              },
    .red=255, .green=255, .blue=255
  },
  
  {/*-- RED LAYER --*/
    .left   = { .onClick={                  .keycode=KEY_M,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onDblClick={               .keycode=KEY_Q,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                        
                .onReleasedClockwise={      .keycode=KEY_UP_ARROW,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onReleasedAntiClockwise={  .keycode=KEY_DOWN_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RIGHT_ARROW, .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_LEFT_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_D,           .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_LEFT_GUI}, 
              },
                 
    .mid    = { .onClick={                  .keycode=KEY_SPACE,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                                       
                .onDblClick={               .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedClockwise={      .keycode=KEY_Y,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedAntiClockwise={  .keycode=KEY_U,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL}, 
              },
    
    .right  = { .onClick={                  .keycode=KEY_TAB,         .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL},  
                .onDblClick={               .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
                .onReleasedClockwise={      .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_UP,         .skipDebounce=1,  .modifier=KEY_RESERVED},           
                .onReleasedAntiClockwise={  .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_DOWN,       .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_NEXT,              .skipDebounce=0,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_PREVIOUS,          .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
              },
    .red=255, .green=0, .blue=0
  },
  

  {/*-- GREEN LAYER --*/
    .left   = { .onClick={                  .keycode=KEY_M,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onDblClick={               .keycode=KEY_Q,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                        
                .onReleasedClockwise={      .keycode=KEY_UP_ARROW,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onReleasedAntiClockwise={  .keycode=KEY_DOWN_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RIGHT_ARROW, .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_LEFT_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_D,           .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_LEFT_GUI}, 
              },
                 
    .mid    = { .onClick={                  .keycode=KEY_SPACE,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                                       
                .onDblClick={               .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedClockwise={      .keycode=KEY_Y,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedAntiClockwise={  .keycode=KEY_U,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL}, 
              },
    
    .right  = { .onClick={                  .keycode=KEY_TAB,         .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL},  
                .onDblClick={               .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
                .onReleasedClockwise={      .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_UP,         .skipDebounce=1,  .modifier=KEY_RESERVED},           
                .onReleasedAntiClockwise={  .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_DOWN,       .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_NEXT,              .skipDebounce=0,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_PREVIOUS,          .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
              },
    .red=0, .green=255, .blue=0
  },
  {/*-- BLUE LAYER --*/
    .left   = { .onClick={                  .keycode=KEY_M,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onDblClick={               .keycode=KEY_Q,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                        
                .onReleasedClockwise={      .keycode=KEY_UP_ARROW,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onReleasedAntiClockwise={  .keycode=KEY_DOWN_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RIGHT_ARROW, .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_LEFT_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_D,           .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_LEFT_GUI}, 
              },
                 
    .mid    = { .onClick={                  .keycode=KEY_SPACE,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                                       
                .onDblClick={               .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedClockwise={      .keycode=KEY_Y,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedAntiClockwise={  .keycode=KEY_U,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL}, 
              },
    
    .right  = { .onClick={                  .keycode=KEY_TAB,         .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL},  
                .onDblClick={               .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
                .onReleasedClockwise={      .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_UP,         .skipDebounce=1,  .modifier=KEY_RESERVED},           
                .onReleasedAntiClockwise={  .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_DOWN,       .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_NEXT,              .skipDebounce=0,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_PREVIOUS,          .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
              },
    .red=0, .green=0, .blue=255
  },
  {/*-- VIOLET LAYER --*/
    .left   = { .onClick={                  .keycode=KEY_M,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onDblClick={               .keycode=KEY_Q,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                        
                .onReleasedClockwise={      .keycode=KEY_UP_ARROW,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onReleasedAntiClockwise={  .keycode=KEY_DOWN_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RIGHT_ARROW, .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_LEFT_ARROW,  .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_D,           .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_LEFT_GUI}, 
              },
                 
    .mid    = { .onClick={                  .keycode=KEY_SPACE,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},                                       
                .onDblClick={               .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedClockwise={      .keycode=KEY_Y,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onReleasedAntiClockwise={  .keycode=KEY_U,           .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_ENTER,       .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL}, 
              },
    
    .right  = { .onClick={                  .keycode=KEY_TAB,         .consumerKeycode=HID_CONSUMER_UNASSIGNED, .skipDebounce=0,  .modifier=KEY_LEFT_CTRL},  
                .onDblClick={               .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
                .onReleasedClockwise={      .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_UP,         .skipDebounce=1,  .modifier=KEY_RESERVED},           
                .onReleasedAntiClockwise={  .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_DOWN,       .skipDebounce=1,  .modifier=KEY_RESERVED},
                .onPressedClockwise={       .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_NEXT,              .skipDebounce=0,  .modifier=KEY_RESERVED},      
                .onPressedAntiClockwise={   .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_PREVIOUS,          .skipDebounce=0,  .modifier=KEY_RESERVED},
                .onLongPress={              .keycode=KEY_RESERVED,    .consumerKeycode=MEDIA_VOLUME_MUTE,       .skipDebounce=0,  .modifier=KEY_RESERVED},  
              },
    .red=75, .green=0, .blue=230
  }


};



int currentKeyMap = 0;
int sizeKeyMap = sizeof keyMaps / sizeof keyMaps[0];



void sendKeycode(struct KeyCodeDef keyDef){
  if(keyDef.keycode != KEY_RESERVED){
    if(keyDef.modifier != KEY_RESERVED){
      Keyboard.press(keyDef.modifier );
    }
    
    Keyboard.write(keyDef.keycode);
    
    if(keyDef.modifier != KEY_RESERVED){
      Keyboard.release(keyDef.modifier );
    }
  
  }else if(keyDef.consumerKeycode != HID_CONSUMER_UNASSIGNED){
    Consumer.write(keyDef.consumerKeycode);
  } 
}

Encoder         *knob;
AceButton       *button;
KnobKeyMapDef   *knobDef;

int        *isDown;
int        *clicked;
int        *doubleClicked;
int        *longPressed;
long       *oldPosition;
long       *newPosition;
int        keyOffset = 0;

int        pulsesPerDetent = 4;
KeyCodeDef keyCodeToSend = {.keycode=KEY_RESERVED,.consumerKeycode=HID_CONSUMER_UNASSIGNED,.skipDebounce=0,.modifier=KEY_RESERVED};


int lastr = 0;
int lastg = 0;
int lastb = 0;


void loop() {

  newMid = knobMid.read();
  if( midDown==1 && newMid != positionMid && positionMid != -999 && ((millis() - lastDebounceTime) > debounceDelay) ){
    if(newMid > positionMid){
      currentKeyMap = (currentKeyMap+1)%(sizeKeyMap);
    }else{
      currentKeyMap = (currentKeyMap-1)%(sizeKeyMap);
    }
    currentKeyMap += currentKeyMap<0?sizeKeyMap:0;
    Serial.println(currentKeyMap);
    lastDebounceTime = millis();
    positionMid=newMid;
    buttMid.cancelLongPress();

  }

  if( abs(millis()-lastColorUpdate)>100){
    if(lastr != keyMaps[currentKeyMap].red){
      lastr = (keyMaps[currentKeyMap].red+lastr)/2;
      
    }
    if(lastg != keyMaps[currentKeyMap].green){
      lastg = (keyMaps[currentKeyMap].green+lastg)/2;
      
    }
    if(lastb != keyMaps[currentKeyMap].blue){
      lastb = (keyMaps[currentKeyMap].blue+lastb)/2;
      
    }
    analogWrite(9, 255-(lastr/50) );
    analogWrite(6, 255-(lastg/50) );
    analogWrite(5, 255-(lastb/50) );

    lastColorUpdate=millis();
  }

  

    
  
  for(int i=0;i<3;i++){    
    if(i == 0){
      knob = &knobLeft;
      button = &buttLeft;
      isDown = &leftDown;
      clicked = &leftClick;
      doubleClicked = &leftDblClick;
      longPressed   = &leftLongPress;
      oldPosition   = &positionLeft;
      newPosition   = &newLeft;
      knobDef       = &keyMaps[currentKeyMap].left;
    }else if(i== 1){
      knob = &knobMid;
      button = &buttMid;
      isDown = &midDown;
      clicked = &midClick;
      doubleClicked = &midDblClick;
      longPressed   = &midLongPress;
      oldPosition   = &positionMid;
      newPosition   = &newMid;
      knobDef       = &keyMaps[currentKeyMap].mid;
    }else if(i== 2){
      knob = &knobRight;
      button = &buttRight;
      isDown = &rightDown;
      clicked = &rightClick;
      doubleClicked = &rightDblClick;
      longPressed   = &rightLongPress;
      oldPosition   = &positionRight;
      newPosition   = &newRight;
      knobDef       = &keyMaps[currentKeyMap].right;
    }

    button->check();

    if(*clicked == 1){
      sendKeycode(knobDef->onClick);
      *clicked = 0;
    }
    if(*doubleClicked == 1){
      sendKeycode(knobDef->onDblClick);
      *doubleClicked  = 0;
    }

    if(*longPressed == 1){
      sendKeycode(knobDef->onLongPress);
      *longPressed  = 0;
    }

    *newPosition = knob->read();
    if (*oldPosition != *newPosition ){
      
      keyCodeToSend.keycode=KEY_RESERVED;
      keyCodeToSend.consumerKeycode=HID_CONSUMER_UNASSIGNED;
      keyCodeToSend.skipDebounce=0;
      keyCodeToSend.modifier=KEY_RESERVED;

      if(*isDown==0){
        if (*newPosition > *oldPosition  ) {
          keyCodeToSend = knobDef->onReleasedClockwise;
        } else {
          keyCodeToSend = knobDef->onReleasedAntiClockwise;
        }
      }else{
        if (*newPosition > *oldPosition  ) {
          keyCodeToSend = knobDef->onPressedClockwise;
        } else {
          keyCodeToSend = knobDef->onPressedAntiClockwise;
        }
      }
      
      if(keyCodeToSend.skipDebounce == 1 || ((millis() - lastDebounceTime) > debounceDelay)){
        if(*oldPosition  != -999 && ( (*newPosition)%pulsesPerDetent == 0 /*||  keyCodeToSend.skipDebounce == 1*/)){
          if(keyCodeToSend.keycode > KEY_RESERVED || keyCodeToSend.consumerKeycode > HID_CONSUMER_UNASSIGNED){
            sendKeycode(keyCodeToSend);
            button->cancelLongPress();
            lastDebounceTime = millis();
          }
        }
      }
      *oldPosition = *newPosition;
    }
  }


  
  
}
