#include "SLC/Log.h"
#include "SLC/MiniLA.h"

typedef enum {
    PTID_PNULL,
    PTID_PC0,
    PTID_PC1,
    PTID_PS0,
    PTID_PS1,
} PTID_t;

const SLC_R32_t PNULL[] = {0.0f, 0.0f, 1.0f};
// Canvas coordinate
const SLC_R32_t  PC0[] = {50.0f, 440.0f, 1.0f};
const SLC_R32_t  PC1[] = {750.0f, 40.0f, 1.0f};

// Source coordinate
const SLC_R32_t  PS0[] = {-2.0f * SLC_R32_M_PI, -1.5f, 1.0f};
const SLC_R32_t  PS1[] = {2.0f * SLC_R32_M_PI, 1.5f, 1.0f};

#define NUMSIZE     sizeof(SLC_R32_t)

// Converting coordinates from the source space to the canvas coordinates
// Source coordinate Ps = [Xs, Ys, 1]t, 
// Canvas coordinate Pc = [Xc, Yc, 1]t,
// Conversion matrix M = [a 0 c : 0 e f : 0 0 1]
// Generaraized conversion Pc = M * Ps.
// Conversion of rectangle corners
//      PC0 = M * PS0,
//      PC1 = M * PS1,

#pragma region declare functions
// create a matrix
SLCArray_pt App_CreateMat(SLC_I16_t rows, SLC_I16_t columns);

// create MC
SLCArray_pt App_CreateMc();

// create MS
SLCArray_pt App_CreateMs();

// Create ME
SLCArray_pt App_CreateMe();

// Create a point corresponding to ptid
SLCArray_pt App_CreatePoint(PTID_t ptid);
#pragma endregion declare functions

SLCArray_pt App_CreateMat(SLC_I16_t rows, SLC_I16_t columns)
{
    SLC_4I16_t size = { NUMSIZE, columns, rows, 1 };
    SLCArray_pt p = SLCArray_ALLOC(size);
    const int matsize = rows * columns;
    for (int i = 0; i < matsize; i++)
    {
        p->Data.R32[i] = SLC_R32_0;
    }
    return p;
}

// create MC
SLCArray_pt App_CreateMc()
{
    SLCArray_pt p = App_CreateMat(4, 1);
    p->Data.R32[0] = PC0[0];
    p->Data.R32[1] = PC1[0];
    p->Data.R32[2] = PC0[1];
    p->Data.R32[3] = PC1[1];
    return p;
}

// create MS
SLCArray_pt App_CreateMs()
{
    SLCArray_pt p = App_CreateMat(4,4);
    SLC_R32_t recip_xdiff = SLC_R32_1 / (PS1[0] - PS0[0]);
    SLC_R32_t recip_ydiff = SLC_R32_1 / (PS1[1] - PS0[1]);
    p->Data.R32[0] = 1.0f + PS0[0] * recip_xdiff;
    p->Data.R32[1] = -PS0[0] * recip_xdiff;
    p->Data.R32[4] = -recip_xdiff;
    p->Data.R32[5] = recip_xdiff;
    p->Data.R32[10] = 1.0f + PS0[1] * recip_ydiff;
    p->Data.R32[11] = -PS0[1] * recip_ydiff;
    p->Data.R32[14] = -recip_ydiff;
    p->Data.R32[15] = recip_ydiff;
    return p;
}

// Create ME
SLCArray_pt App_CreateMe()
{
    SLCArray_pt pmc = App_CreateMc();
    SLCArray_pt pms = App_CreateMs();
    SLCArray_pt pme = App_CreateMat(4, 1);
    SLCArray_pt pmcwork = App_CreateMat(1, 4);
    SLCMat_R32Multiply(pme, pms, pmc, pmcwork);
    SLC_SAFE_FREE(&pmc);
    SLC_SAFE_FREE(&pms);
    SLC_SAFE_FREE(&pmcwork);
    return pme;
}

// Create transform matrix M
SLCArray_pt App_CreateM()
{
    SLCArray_pt me = App_CreateMe();
    SLCArray_pt m = App_CreateMat(3, 3);
    SLC_R32_t* p_me = me->Data.R32;
    SLC_R32_t* p_m = m->Data.R32;
    p_m[0] = p_me[1]; // a
    p_m[2] = p_me[0]; // c
    p_m[4] = p_me[3]; // e
    p_m[5] = p_me[2]; // f
    p_m[8] = SLC_R32_1; //1.0f
    SLC_SAFE_FREE(&me);
    return m;
}

// Create a point corresponding to ptid
SLCArray_pt App_CreatePoint(PTID_t ptid)
{
    SLC_4I16_t dims = {NUMSIZE, 1, 3, 1};
    SLCArray_pt p = SLCArray_ALLOC(dims);
    switch (ptid)
    {
    case PTID_PNULL:
        SLC_COPY3(p->Data.R32, PNULL);
        break;
    case PTID_PC0:
        SLC_COPY3(p->Data.R32, PC0);
        break;
    case PTID_PC1:
        SLC_COPY3(p->Data.R32, PC1);
        break;
    case PTID_PS0:
        SLC_COPY3(p->Data.R32, PS0);
        break;
    case PTID_PS1:
        SLC_COPY3(p->Data.R32, PS1);
        break;
    }
    return p;
}

int main()
{
    const char* SEPARATOR = "---\n";
    SLC_errno_t err = 0;
    SLCArray_pt m = NULL, vwork = NULL, pc = NULL;
    do {
        vwork = App_CreateMat(1, 3);
        pc = App_CreateMat(3, 1);
        m = App_CreateM();
        SLCMat_R32Print(stdout, "main:m", m, SEPARATOR);
        SLCArray_pt ps = App_CreatePoint(PTID_PS0);
        SLCMat_R32Print(stdout, "main.PS0", ps, SEPARATOR);
        SLCMat_R32Multiply(pc, m, ps, vwork);
        SLCMat_R32Print(stdout, "main:pc0", pc, SEPARATOR);
        SLC_SAFE_FREE(&ps);
        ps = App_CreatePoint(PTID_PS1);
        SLCMat_R32Print(stdout, "main.PS1", ps, SEPARATOR);
        SLCMat_R32Multiply(pc, m, ps, vwork);
        SLCMat_R32Print(stdout, "main:pc1", pc, SEPARATOR);
        SLC_SAFE_FREE(&ps);
    } while (0);
    SLC_SAFE_FREE(&m);
    SLC_SAFE_FREE(&vwork);
    SLC_SAFE_FREE(&pc);
    return err;
}