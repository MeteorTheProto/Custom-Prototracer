#include <Arduino.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/KaiborgV1Pixels.h"
#include "..\Sensors\APDS9960.h"

#include "..\Menu\SingleButtonMenu.h"

#include "..\Sensors\SerialSync.h"

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class KaiborgV1D1Controller : public Controller {
    
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
    KaiborgV1D1Controller(uint8_t maxBrightness) : Controller(cameras, 2, maxBrightness, 0){}
 
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
                leds.setPixel(0, 0, 10, 6); //aqua for boop
            } else {
                switch (currentExpression)
                {
                case 0:
                    /* code */
                    break;
                
                default:
                    break;
                }
            }
            /*
             if (mode == 0) Default();
            else if (mode == 1) Blushing();
            else if (mode == 2) Surprised();
            else if (mode == 3) BoopFace();
            else if (mode == 4) Sad();
            else if (mode == 5) Angry();
            else if (mode == 6) SpectrumAnalyzerWithFace();
            else if (mode == 7) SpectrumAnalyzerNoFace();
            else Sleepy();
            */
            if (currentExpression == 0) {
                leds.setPixel(0, 8, 7, 2); //yellow for happy
            } else if (currentExpression == 1) {
                leds.setPixel(0, 9, 3, 3); //lightpink blush
            }else if (currentExpression == 2) {
                leds.setPixel(0, 10, 0, 0); //red for angry
            } else if (currentExpression == 3) {
                leds.setPixel(0, 6, 3, 10); //purple for surprise
            } else if (currentExpression == 4) {
                leds.setPixel(0, 0, 2, 9); //blue for sad
            } else if (currentExpression == 5) {
                leds.setPixel(0, 0, 10, 0); //boop face
            } else if (currentExpression == 6) {
                leds.setPixel(0, 7, 0, 2); //bright pink for SA
            } else if (currentExpression == 7) {
                leds.setPixel(0, 9, 0, 9); //light pink for SA no face
            } else if (currentExpression == 8) {
                leds.setPixel(0, 0, 0, 2); //blue for sad
            } else {
                leds.setPixel(0, 26, 15, 0); //orange for error
            }
        
        } else {
            leds.setPixel(0,0,0,0); //pixel off
        }

        leds.show();
    }

    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
        leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
    }
};
