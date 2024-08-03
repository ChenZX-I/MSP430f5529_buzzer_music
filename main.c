#include <msp430.h> 
#include "pitches.h"

/**
 * buzzer2.c
 */
void music();
int melody[] = {
NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5,
NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
NOTE_G4, 0, NOTE_G4, NOTE_D5,
NOTE_C5, 0, NOTE_AS4, 0,
NOTE_A4, 0, NOTE_A4, NOTE_A4,
NOTE_C5, 0, NOTE_AS4, NOTE_A4,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
NOTE_G4, 0, NOTE_G4, NOTE_D5,
NOTE_C5, 0, NOTE_AS4, 0,
NOTE_A4, 0, NOTE_A4, NOTE_A4,
NOTE_C5, 0, NOTE_AS4, NOTE_A4,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
};
/*int melody[] = {
1,10,100,100,10,1
}*/
//�������ܣ���ʼ��������P3.6��LED_P1.0
void Init_Buzzer_Led()
{
    P1DIR |= BIT2;
    P1SEL |= BIT2;             //����TA0.1Ϊ���
    //P1OUT &= ~BIT0;             //����P1.0�ƣ�����Ϊ���ģʽ����Ϩ��
    P3DIR |= BIT6;
    //P3OUT &= ~BIT6;             //���÷�����������Ϊ���ģʽ���ȹر�
    P8DIR |= BIT1;


}

int main(int temn, int temy)//��ǰ�¶ȣ��¶���ֵ
{


        WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

        Init_Buzzer_Led();



        music();

}
unsigned int beep = 0;
unsigned int time = 0;

//�������ܣ��ı�Ƶ��
void music()
{

    //��ΪtimerA0�ĳ�ʼ��
    TA0CCTL1 = OUTMOD_7;
    TA0CTL |= MC_1 + TASSEL_2 + TACLR;
    TA0CCTL0 = CCIE;

    //��ΪtimerA1�ĳ�ʼ��
    TA1CTL |= MC_1 + TASSEL_2 + TACLR ;
    TA1CCTL0 = CCIE;
    TA1CCR0 = 250;
    TA1CCTL1 = OUTMOD_7;
    TA1CCR1 = 0;

    __enable_interrupt();

}
unsigned i = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR (void)
{
    P3OUT ^= BIT6;

}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TimerA1_ISR (void)
{
    time++;
    if(time == 1000)
    {
        beep++;
        if(beep > 80)
        {
            beep = 0;
        }
        time = 0;


        TA0CCR0  = 1000000/melody[beep];
    }

}

