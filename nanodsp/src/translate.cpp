//
// Frequency translator
//
// Copyright 2010-2013 Moe Wheatley
// Copyright 2014      Alexandru Csete
// All rights reserved.
//
// This software is released under the Simplified BSD License, see
// license.txt for details
//
#include <stdlib.h>
#include "translate.h"


Translate::Translate()
{
    sample_rate = 96000.0;
    nco_freq = 0.0;
    cw_offset = 0.0;
    nco_inc = 0.0;
    osc_cos = 1.0;
    osc_sin = 0.0;

    osc1.re = 1.0;
    osc1.im = 0.0;
}


void Translate::set_nco_frequency(real_t freq_hz)
{
    nco_freq = freq_hz + cw_offset;
    nco_inc = K_2PI * nco_freq / sample_rate;
    osc_cos = MCOS(nco_inc);
    osc_sin = MSIN(nco_inc);
}

void Translate::set_cw_offset(real_t offset_hz)
{
    real_t real_nco = nco_freq - cw_offset;
    cw_offset = offset_hz;
    set_nco_frequency(real_nco);
}

void Translate::set_sample_rate(real_t rate)
{
    if(sample_rate != rate)
    {
        real_t real_nco = nco_freq - cw_offset;
        sample_rate = rate;
        set_nco_frequency(real_nco);
    }
}

void Translate::process(int length, complex_t* data)
{
    complex_t  dtmp;
    complex_t  osc;
    real_t     osc_gn;
    int        i;

    for (i = 0; i < length; i++)
    {
        dtmp.re = data[i].re;
        dtmp.im = data[i].im;

        osc.re = osc1.re * osc_cos - osc1.im * osc_sin;
        osc.im = osc1.im * osc_cos + osc1.re * osc_sin;
        //osc_gn = 1.95 - (osc1.re * osc1.re + osc1.im * osc1.im);
        osc_gn = 1.99 - (osc1.re * osc1.re + osc1.im * osc1.im);
        osc1.re = osc_gn * osc.re;
        osc1.im = osc_gn * osc.im;

        // complex multiply by shift frequency
        data[i].re = ((dtmp.re * osc.re) - (dtmp.im * osc.im));
        data[i].im = ((dtmp.re * osc.im) + (dtmp.im * osc.re));
    }

}
