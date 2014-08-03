//
// Unit test for the frequency translator
//
// Copyright 2014 Alexandru Csete
// All rights reserved.
//
// This software is released under the Simplified BSD License, see
// license.txt for details
//

#include <stdio.h>
#include <stdlib.h>

// nanodsp includes
#include <datatypes.h>
#include <translate.h>


// Generate n-samples of complex sine wave
complex_t* gen_cplx_sine_wave(int n, real_t freq, real_t sample_rate)
{
    complex_t* data = (complex_t *) malloc(n * sizeof(complex_t));
    int i;

    real_t nco_inc  = K_2PI * freq / sample_rate;
    real_t nco_time = nco_inc;

    fprintf(stderr, "NCO_INC: %f\n", nco_inc);

    for (i = 0; i < n; i++)
    {
        data[i].re = MSIN(nco_time);
        data[i].im = MCOS(nco_time);
        nco_time += nco_inc;
        nco_time = MFMOD(nco_time, K_2PI);
    }

    return data;
}

// Compare two complex array for equality.
// Return the number of elements where the difference in either real or
// imaginary parts was greater than eps
int compare_cplx_arrays(int n, const complex_t* d1, const complex_t* d2,
                        const real_t eps)
{
    int i;
    int error = 0;

    for (i = 0; i < n; i++)
    {
        if ((MFABS(d1[i].re - d2[i].re) > eps) ||
            (MFABS(d1[i].im - d2[i].im) > eps))
        {
            fprintf(stderr,
                    "%s: I:%d   RE1:%f    RE2:%f    IM1:%f    IM2:%f\n",
                    __func__, i, d1[i].re, d2[i].re, d1[i].im, d2[i].im);
            error++;
        }
    }

    return error;
}

// Dump a complex array to stderr
void dump_cplx_array(const char *message, const complex_t* data, int n)
{
    int i;

    if (message != NULL)
        fprintf(stderr, "%s\n", message);

    for (i = 0; i < n; i++)
        fprintf(stderr, " %f    %f\n", data[i].re, data[i].im);
}


static int test_translation(const char *test_id,
                            int n, real_t fs, real_t f0,
                            real_t nco, real_t cw_offs, real_t tol)
{
    Translate translator;

    int errors = 0;

    fprintf(stderr, "%s:\n", test_id);
    fprintf(stderr, "    Fs  = %f Hz\n", fs);
    fprintf(stderr, "    F0  = %f Hz\n", f0);
    fprintf(stderr, "    NCO = %f Hz\n", nco);
    fprintf(stderr, "    CWO = %f Hz\n", cw_offs);

    // Generate sine waves
    complex_t* data1 = gen_cplx_sine_wave(n, f0, fs);
    complex_t* data2 = gen_cplx_sine_wave(n, f0 - (nco + cw_offs), fs);

    // initialize frequency translator and process the data
    translator.set_sample_rate(fs);
    translator.set_nco_frequency(nco);
    translator.set_cw_offset(cw_offs);
    translator.process(n, data1);

    fprintf(stderr, "    Check results\n");
    errors += compare_cplx_arrays(n, data1, data2, tol);
    fprintf(stderr, "**** ERRORS: %d\n", errors);
    if (errors)
    {
        dump_cplx_array("DATA1:", data1, n);
        dump_cplx_array("DATA2:", data2, n);

        goto finish;
    }

finish:
    free(data1);
    free(data2);

    return errors;

}

static int run_test_01(void)
{
    return test_translation("TEST 01",
                            50000,       // 5000 samples
                            48000.0,    // 48 ksps
                            0.0,        // 0 Hz sine wave
                            0.0,        // 0 Hz NCO
                            0.0,        // 0 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}

static int run_test_02(void)
{
    return test_translation("TEST 02",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            1000.0,     // 1 kHz sine wave
                            0.0,        // 0 Hz NCO
                            0.0,        // 0 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}

static int run_test_03(void)
{
    return test_translation("TEST 03",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            0.0,        // 0 Hz sine wave 
                            1700.0,     // 17 kHz NCO
                            0.0,        // 0 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}


static int run_test_04(void)
{
    return test_translation("TEST 04",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            5000.0,     // 5 kHz sine wave
                            9000.0,     // 9 kHz NCO
                            0.0,        // 0 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}

static int run_test_05(void)
{
    return test_translation("TEST 05",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            -5000.0,    // -5 kHz sine wave
                            9000.0,     // 13 kHz NCO
                            0.0,        // 0 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}

static int run_test_06(void)
{
    return test_translation("TEST 06",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            15000.0,    // 15 kHz sine wave
                            -15000.0,   // -15 kHz NCO
                            0.0,        // 0 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}

static int run_test_07(void)
{
    return test_translation("TEST 07",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            1000.0,     // 1 kHz sine wave
                            0.0,        // 0 Hz NCO
                            800.0,      // 800 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}

static int run_test_08(void)
{
    return test_translation("TEST 8",
                            5000,       // 5000 samples
                            48000.0,    // 48 ksps
                            47000.0,    // 47 kHz sine wave
                            -46000.0,   // -46 kHz NCO
                            800.0,      // 800 Hz CW offset
                            0.01);      // FIXME: 0.5% tolerance
}


int main(void)
{
    int result = 0;

    result |= run_test_01();
    result |= run_test_02();
    result |= run_test_03();
    result |= run_test_04();
    result |= run_test_05();
    result |= run_test_06();
    result |= run_test_07();
    result |= run_test_08();

    return result;
}
