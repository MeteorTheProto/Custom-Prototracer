#include <Arduino.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/KaiborgV1Pixels.h"
#include "..\Sensors\APDS9960.h"

#include "..\Menu\SingleButtonMenu.h"

#include "..\Sensors\SerialSync.h"

/** Meteor Defines*/
#include "MeteorDefines.h"

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class MeteorV1D1Controller : public Controller {
    
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camRghtTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camLeftTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

    PixelGroup<571> camRghtPixels = PixelGroup<571>(KaiborgV1Pixels, IPixelGroup::ZEROTOMAX);
    PixelGroup<571> camLeftPixels = PixelGroup<571>(KaiborgV1Pixels, IPixelGroup::MAXTOZERO);

    Camera<571> camRght = Camera<571>(&camRghtTransform, &cameraLayout, &camRghtPixels);
    Camera<571> camLeft = Camera<571>(&camLeftTransform, &cameraLayout, &camLeftPixels);

    CameraBase* cameras[2] = { &camRght, &camLeft };

public:
    MeteorV1D1Controller(uint8_t maxBrightness) : Controller(cameras, 2, maxBrightness, 0){}
 
    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        int offset;

        for (int i = 0; i < 571; i++){
            *camLeftPixels.GetColor(i) = camLeftPixels.GetColor(i)->Scale(brightness);
            *camRghtPixels.GetColor(i) = camRghtPixels.GetColor(i)->Scale(brightness);
        }

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                offset = i + 225;

                leds.setPixel(i + 346 * 4, camLeftPixels.GetColor(offset)->R, camLeftPixels.GetColor(offset)->G, camLeftPixels.GetColor(offset)->B);//Pin 7
                leds.setPixel(i + 346 * 5, camRghtPixels.GetColor(i)->R, camRghtPixels.GetColor(i)->G, camRghtPixels.GetColor(i)->B);//Pin 8
            } else {
                offset = i - 346;

                leds.setPixel(i + 346 * 6 - 346, camLeftPixels.GetColor(offset)->R, camLeftPixels.GetColor(offset)->G, camLeftPixels.GetColor(offset)->B);//Pin 8
                leds.setPixel(i + 346 * 7 - 346, camRghtPixels.GetColor(i)->R, camRghtPixels.GetColor(i)->G, camRghtPixels.GetColor(i)->B);//Pin 8
            }
        }

        bool isBeingBooped = APDS9960::isBooped();
        bool enableIndicator = !SerialSync::GetDead();
        uint8_t currentExpression = Menu::GetFaceState();

        if (enableIndicator) {
            if (isBeingBooped == true){
              SetIndicator(BoopLED); //aqua for boop
            } else {
                switch (currentExpression){
                case HappyFace:
                    SetIndicator(HappyLED);
                    break;
                
                case BlushFace:
                    SetIndicator(BlushingLED);
                    break;

                case SurpriseFace:
                    SetIndicator(SurpriseLED);
                    break;

                case AngryFace:
                    SetIndicator(AngryLED);
                    break;

                case BoopFace:
                    SetIndicator(BoopLED);
                    break;

                case SadFace:
                    SetIndicator(SadLED);
                    break;

                case SpectrumAnalyzerNoFace:
                    SetIndicator(SpectrumLED);
                    break;

                case SpectrumAnalyzerWithFace:
                    SetIndicator(SpectrumFaceLED);
                    break;

                case SleepFace:
                    SetIndicator(SleepyLED);
                    break;

                default:
                    SetIndicator(orange);
                    break;
                }
            }
           
        leds.show();
    }
    }
    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
        leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
    }
    void SetIndicator(RGBColor color) {
        leds.setPixel(0, color.R, color.B,color.G);
    }
};
