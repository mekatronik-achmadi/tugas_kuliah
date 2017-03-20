#include "gfx.h"
#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include <string.h>

GHandle ghlblADC0,ghlblADC1,ghlblADC2,ghlblADC3;
GHandle ghlblADC4,ghlblADC5,ghlblADC6,ghlblADC7;
GHandle ghlblPolar,ghlblAzimuth;

#define ADC_GRP1_NUM_CHANNELS   8
#define ADC_GRP1_BUF_DEPTH      10

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

adcsample_t adc0,adc1,adc2,adc3,adc4,adc5,adc6,adc7;
uint32_t sum_adc0,sum_adc1,sum_adc2,sum_adc3,sum_adc4,sum_adc5,sum_adc6,sum_adc7;

uint16_t ang_polar,ang_azimuth;

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void) buffer; (void) n;
  int i;
  if (adcp->state == ADC_COMPLETE) {

    sum_adc0=0;
    sum_adc1=0;
    sum_adc2=0;
    sum_adc3=0;
    sum_adc4=0;
    sum_adc5=0;
    sum_adc6=0;
    sum_adc7=0;

    for(i=0;i<ADC_GRP1_BUF_DEPTH;i++){
        sum_adc0=sum_adc0+samples[0+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc1=sum_adc1+samples[1+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc2=sum_adc2+samples[2+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc3=sum_adc3+samples[3+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc4=sum_adc4+samples[4+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc5=sum_adc5+samples[5+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc6=sum_adc6+samples[6+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc7=sum_adc7+samples[7+(i*ADC_GRP1_NUM_CHANNELS)];
    }

    adc0=sum_adc0/ADC_GRP1_BUF_DEPTH;
    adc1=sum_adc1/ADC_GRP1_BUF_DEPTH;
    adc2=sum_adc2/ADC_GRP1_BUF_DEPTH;
    adc3=sum_adc3/ADC_GRP1_BUF_DEPTH;
    adc4=sum_adc4/ADC_GRP1_BUF_DEPTH;
    adc5=sum_adc5/ADC_GRP1_BUF_DEPTH;
    adc6=sum_adc6/ADC_GRP1_BUF_DEPTH;
    adc7=sum_adc7/ADC_GRP1_BUF_DEPTH;

   }
 }

static const ADCConversionGroup adcgrpcfg = {
    FALSE,
    ADC_GRP1_NUM_CHANNELS,
    adccb,
    NULL,
    /* HW dependent part.*/
    0,
    0,
    ADC_SMPR2_SMP_AN0(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN1(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN2(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN3(ADC_SAMPLE_239P5) |
    ADC_SMPR2_SMP_AN4(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN5(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN6(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN7(ADC_SAMPLE_239P5),
    0,
    ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
    ADC_SQR2_SQ7_N(ADC_CHANNEL_IN6) | ADC_SQR2_SQ8_N(ADC_CHANNEL_IN7),
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2) | ADC_SQR3_SQ4_N(ADC_CHANNEL_IN3) |
    ADC_SQR3_SQ5_N(ADC_CHANNEL_IN4) | ADC_SQR3_SQ6_N(ADC_CHANNEL_IN5)

};

static THD_WORKING_AREA(wa_adcThread, 128);
static THD_FUNCTION(adcThread,arg) {
  (void)arg;

  while (TRUE) {
    chThdSleepMilliseconds(100);
    adcStartConversion(&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
  }
}

char txt_adc[6];
char txt_angle[6];

static void TextUpdate(void){

    chsnprintf(txt_adc,6,"%4i",adc0);
    gwinSetText(ghlblADC0, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc1);
    gwinSetText(ghlblADC1, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc2);
    gwinSetText(ghlblADC2, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc3);
    gwinSetText(ghlblADC3, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc4);
    gwinSetText(ghlblADC4, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc5);
    gwinSetText(ghlblADC5, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc6);
    gwinSetText(ghlblADC6, txt_adc, TRUE);

    chsnprintf(txt_adc,6,"%4i",adc7);
    gwinSetText(ghlblADC7, txt_adc, TRUE);

    chsnprintf(txt_angle,6,"%4i",ang_polar);
    gwinSetText(ghlblPolar, txt_angle, TRUE);

    chsnprintf(txt_angle,6,"%4i",ang_azimuth);
    gwinSetText(ghlblAzimuth, txt_angle, TRUE);

    chThdSleepMilliseconds(100);
}

//========================================================

static THD_WORKING_AREA(waBlink, 128);
static THD_FUNCTION(thdBlink, arg) {

  (void)arg;

  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOE, 5);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOE, 5);
    chThdSleepMilliseconds(500);
  }
}

//========================================================

float calibrationData[] = {
    -0.06678,		// ax
    -0.00187,		// bx
    259.06353,		// cx
    0.00039,		// ay
    0.09974,		// by
    -31.92561 		// cy
};

bool_t LoadMouseCalibration(unsigned instance, void *data, size_t sz)
{
    (void)instance;

    if (sz != sizeof(calibrationData) || instance != 0) {
        return FALSE;
    }

    memcpy(data, (void*)&calibrationData, sz);

    return TRUE;
}

//========================================================

static void createWidgets(void) {
    GWidgetInit	wi;

    // Apply some default values for GWIN
    gwinWidgetClearInit(&wi);
    wi.g.show = TRUE;

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 10, wi.g.y = 60;
    wi.text = "0";
    ghlblADC0 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC0, 50, "ADC0:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 10, wi.g.y = 80;
    wi.text = "0";
    ghlblADC1 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC1, 50, "ADC1:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 10, wi.g.y = 100;
    wi.text = "0";
    ghlblADC2 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC2, 50, "ADC2:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 10, wi.g.y = 120;
    wi.text = "0";
    ghlblADC3 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC3, 50, "ADC3:");


    wi.g.width = 100; wi.g.height = 20; wi.g.x = 130, wi.g.y = 60;
    wi.text = "0";
    ghlblADC4 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC4, 50, "ADC4:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 130, wi.g.y = 80;
    wi.text = "0";
    ghlblADC5 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC5, 50, "ADC5:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 130, wi.g.y = 100;
    wi.text = "0";
    ghlblADC6 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC6, 50, "ADC6:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 130, wi.g.y = 120;
    wi.text = "0";
    ghlblADC7 = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblADC7, 50, "ADC7:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 10, wi.g.y = 160;
    wi.text = "0";
    ghlblPolar = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblPolar, 50, "P:");

    wi.g.width = 100; wi.g.height = 20; wi.g.x = 130, wi.g.y = 160;
    wi.text = "0";
    ghlblAzimuth = gwinLabelCreate(0, &wi);
    gwinLabelSetAttribute(ghlblAzimuth, 50, "A:");

}

int main(void) {

    // Initialize the display
    gfxInit();

    palSetPadMode(GPIOA,0,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,1,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,2,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,3,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,4,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,5,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,6,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,7,PAL_MODE_INPUT_ANALOG);

    adcStart(&ADCD1, NULL);
    chThdCreateStatic(wa_adcThread, sizeof(wa_adcThread), NORMALPRIO, adcThread, NULL);

    palSetPadMode(GPIOE,5,PAL_MODE_OUTPUT_PUSHPULL);
    chThdCreateStatic(waBlink, sizeof(waBlink), NORMALPRIO, thdBlink, NULL);

    // Set the widget defaults
    gwinSetDefaultFont(gdispOpenFont("*"));
    gwinSetDefaultStyle(&WhiteWidgetStyle, FALSE);
    gdispClear(White);
    gdispSetOrientation(GDISP_ROTATE_90);

    // create the widget
    createWidgets();

    while(1) {
        TextUpdate();
    }

    return 0;
}
