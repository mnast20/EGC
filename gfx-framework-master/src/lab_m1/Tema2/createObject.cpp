#include "createObject.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

glm::vec3 d1, d2;
glm::vec3 p;

std::vector<glm::vec3> racetrack_margins;

std::vector<glm::vec3> middle_positions = {
    // 0 --> 0
    glm::vec3(0.33157f, 0.01f, -2.27566f),

    // 1 --> 1
    glm::vec3(-0.2207f, 0.01f, -2.27855f),

    // 2 --> 2
    glm::vec3(-0.79463f, 0.01f, -2.29386f),

    // 3 --> 3
    glm::vec3(-1.45273f, 0.01f, -2.30151f),

    // 4 --> 4
    glm::vec3(-2.18735f, 0.01f, -2.31681f),

    // 5 --> 5
    glm::vec3(-2.8531f, 0.01f, -2.31681f),

    // 6 --> 6
    glm::vec3(-3.58007f, 0.01f, -2.32447f),

    // 7 --> 7
    glm::vec3(-4.13869f, 0.01f, -2.33212f),

    // 8 --> 8
    glm::vec3(-4.79678f, 0.01f, -2.33977f),

    // 9 --> 9
    glm::vec3(-5.3401f, 0.01f, -2.34742f),

    // 10 --> 10
    glm::vec3(-5.95086f, 0.01f, -2.36152f),

    // 11 --> 11
    glm::vec3(-6.33864f, 0.01f, -2.33411f),

    // 12 --> 12
    glm::vec3(-6.61867f, 0.01f, -2.24845f),

    // 13 --> 13
    glm::vec3(-6.80646f, 0.01f, -2.08702f),

    // C --> 14
    glm::vec3(-6.88882f, 0.01f,-1.95195f),

    // 14 --> 15
    glm::vec3(-6.92836f, 0.01f, -1.83664f),

    // D --> 16
    glm::vec3(-6.94483f, 0.01f, -1.71145f),

    // E --> 17
    glm::vec3(-6.94154, 0.01f, -1.60602),

    // 15 --> 18
    glm::vec3(-6.92506f, 0.01f, -1.50719f),

    // F --> 19
    glm::vec3(-6.86906f, 0.01f, -1.36882f),

    // G --> 20
    glm::vec3(-6.82952f, 0.01f,-1.28316f),

    // 16 --> 21
    glm::vec3(-6.78088, 0.01f, -1.17373),

    // 17 --> 22
    glm::vec3(-6.57585,0.01f, -0.69345),

    // 18 --> 23
    glm::vec3(-6.35156f, 0.01f, -0.18629f),

    // 19 --> 24
    glm::vec3(-6.10827f, 0.01f, 0.37183f),

    // 20 --> 25
    glm::vec3(-5.90047f, 0.01f, 0.87803f),

    // 21 --> 26
    glm::vec3(-5.69621f,0.01f, 1.36891f),

    // 22 --> 27
    glm::vec3(-5.53584f, 0.01f, 1.81722f),

    // 23 --> 28
    glm::vec3(-5.30687f, 0.01f, 2.34672f),

    // 24 --> 29
    glm::vec3(-5.13514f, 0.01f, 2.83328f),

    // 25 --> 30
    glm::vec3(-4.93479f, 0.01f, 3.29123f),

    // 26 --> 31
    glm::vec3(-4.83781f, 0.01f, 3.51147f),

    // 27 --> 32
    glm::vec3(-4.72906f, 0.01f, 3.65318f),

    // 28 --> 33
    glm::vec3(-4.62863f, 0.01f, 3.75074f),

    // 29 --> 34
    glm::vec3(-4.49089f, 0.01f, 3.84544f),

    // 30 --> 35
    glm::vec3(-4.35889f, 0.01f, 3.90857f),

    // J --> 36
    glm::vec3(-4.26f, 0.01f, 3.94f),

    // K --> 37
    glm::vec3(-4.2f, 0.01f, 3.95f),

    // L --> 38
    glm::vec3(-4.16f, 0.01f, 3.96f),

    // M --> 39
    glm::vec3(-4.12f, 0.01f, 3.97f),

    // N --> 40
    glm::vec3(-4.09f, 0.01f, 3.97f),

    // O --> 41
    glm::vec3(-4.05f, 0.01f, 3.97f),

    // P --> 42
    glm::vec3(-4.02f, 0.01f, 3.97f),

    // Q --> 43
    glm::vec3(-3.97f, 0.01f, 3.97f),

    // S --> 44
    glm::vec3(-3.92f, 0.01f, 3.97f),

    // T --> 45
    glm::vec3(-3.87f, 0.01f, 3.96f),

    // U --> 47
    glm::vec3(-3.81f, 0.01f, 3.95f),

    // V --> 48
    glm::vec3(-3.77f, 0.01f, 3.94f),

    // W --> 49
    glm::vec3(-3.72f, 0.01f, 3.93f),

    // Z --> 50
    glm::vec3(-3.68f, 0.01f, 3.91f),

    // A1 --> 51
    glm::vec3(-3.62f, 0.01f, 3.89f),

    // B1 --> 52
    glm::vec3(-3.59f, 0.01f, 3.87f),

    // C1 --> 53
    glm::vec3(-3.53f, 0.01f, 3.84f),

    // D1 --> 54
    glm::vec3(-3.49f, 0.01f, 3.82f),

    // E1 --> 55
    glm::vec3(-3.45f, 0.01f, 3.79f),

    // F1 --> 56
    glm::vec3(-3.42f, 0.01f, 3.77f),

    // G1 --> 57
    glm::vec3(-3.38f, 0.01f, 3.74f),

    // H1 --> 58
    glm::vec3(-3.36f, 0.01f, 3.71f),

    // I1 --> 59
    glm::vec3(-3.33f, 0.01f, 3.69f),

    // G5 --> 60
    glm::vec3(-3.32443f, 0.01f, 3.68484f),

    // H5 --> 61
    glm::vec3(-3.31653f, 0.01f, 3.67764f),

    // 31 --> 62
    glm::vec3(-3.30932f, 0.01f, 3.66997f),

    // I5 --> 63
    glm::vec3(-3.30375f, 0.01f, 3.6623f),

    // J5 --> 64
    glm::vec3(-3.29863f, 0.01f, 3.65323f),

    // J1 --> 65
    glm::vec3(-3.29538f, 0.01f, 3.64556f),

    // K5 --> 66
    glm::vec3(-3.29282f, 0.01f, 3.63813f),

    // L5 --> 67
    glm::vec3(-3.28887f, 0.01f, 3.62883f),

    // M5 --> 68
    glm::vec3(-3.28631f, 0.01f, 3.61883f),

    // K1 --> 69
    glm::vec3(-3.28399f, 0.01f, 3.60994f),

    // N5 --> 70
    glm::vec3(-3.28212f, 0.01f, 3.60102f),

    // O5 --> 71
    glm::vec3(-3.28043f, 0.01f, 3.59332f),

    // P5 --> 72
    glm::vec3(-3.27958f, 0.01f, 3.5829f),

    // L1 --> 73
    glm::vec3(-3.27963f, 0.01f, 3.57544f),

    // M1 --> 74
    glm::vec3(-3.28145, 0.01f, 3.53256),

    // N1 --> 75
    glm::vec3(-3.28338f, 0.01f, 3.50053f),

    // O1 --> 76
    glm::vec3(-3.28962f, 0.01f, 3.46433f),

    // P1 --> 77
    glm::vec3(-3.29836f, 0.01f, 3.42563f),

    // 32 --> 78
    glm::vec3(-3.31334f, 0.01f, 3.38443f),

    // 33 --> 79
    glm::vec3(-3.41785f, 0.01f, 3.10519f),

    // 34 --> 80
    glm::vec3(-3.50372f, 0.01f, 2.77604f),

    // 35 --> 81
    glm::vec3(-3.6182f, 0.01f, 2.43258f),

    // 36 --> 82
    glm::vec3(-3.70407f, 0.01f, 2.10343f),

    // 37 --> 83
    glm::vec3(-3.84717f, 0.01f, 1.6598f),

    // 38 --> 84
    glm::vec3(-3.93304f, 0.01f, 1.28772f),

    // 39 --> 85
    glm::vec3(-3.95f, 0.01f, 1.0f),

    // 40 --> 86
    glm::vec3(-3.89011f, 0.01f, 0.74391f),

    // 41 --> 87
    glm::vec3(-3.747f, 0.01f, 0.50063f),

    // 42 --> 88
    glm::vec3(-3.54665f, 0.01f, 0.30028f),

    // 43 --> 89
    glm::vec3(-3.3463f, 0.01f, 0.17148f),

    // 44 --> 90
    glm::vec3(-3.13164f, 0.01f, 0.08562f),

    // 45 --> 91
    glm::vec3(-2.84542f, 0.01f, -0.00025f),

    // 46 --> 92
    glm::vec3(-2.55921f, 0.01f, -0.05749f),

    // 47 --> 93
    glm::vec3(-2.20144f, 0.01f, -0.05749f),

    // 48 --> 94
    glm::vec3(-1.7578f, 0.01f, -0.02887f),

    // 49 --> 95
    glm::vec3(-1.24262f, 0.01f, 0.07131f),

    // 50 --> 96
    glm::vec3(-0.87054f, 0.01f, 0.14286f),

    // 51 --> 97
    glm::vec3(-0.48415, 0.01f, 0.2001),

    // 52 --> 98
    glm::vec3(-0.09776f, 0.01f, 0.25735f),

    // 53 --> 99
    glm::vec3(0.34588f, 0.01f, 0.31459f),

    // 54 --> 100
    glm::vec3(0.7752f, 0.01f, 0.40045f),

    // 55 --> 101
    glm::vec3(1.31901f, 0.01f, 0.50063f),

    // 56 --> 102
    glm::vec3(1.92006f, 0.01f, 0.60081f),

    // 57 --> 103
    glm::vec3(2.36369f, 0.01f, 0.65805f),

    // 58 --> 104
    glm::vec3(2.93613f, 0.01f, 0.75822f),

    // 59 --> 105
    glm::vec3(3.40838f, 0.01f, 0.84409f),

    // 60 --> 106
    glm::vec3(3.79477f, 0.01f, 0.91564f),

    // 61 --> 107
    glm::vec3(4.18116f, 0.01f, 1.05875f),

    // 62 --> 108
    glm::vec3(4.56755f, 0.01f, 1.24479f),

    // 63 --> 109
    glm::vec3(4.95394f, 0.01f, 1.51669f),

    // 64 --> 110
    glm::vec3(5.22585f, 0.01f, 1.75998f),

    // 65 --> 111
    glm::vec3(5.40823f, 0.01f, 1.96142f),

    // W1 --> 112
    glm::vec3(5.43997f, 0.01f, 2.00726f),

    // C2 --> 113
    glm::vec3(5.45878f, 0.01f, 2.05192f),

    // Z1 --> 114
    glm::vec3(5.45878f, 0.01f, 2.09306f),

    // V1 --> 115
    glm::vec3(5.4482f, 0.01f, 2.13302f),

    // U1 --> 116
    glm::vec3(5.43174f, 0.01f, 2.17181f),

    // 66 --> 117
    glm::vec3(5.40236f, 0.01f, 2.21295f),

    // A2 --> 118
    glm::vec3(5.37297f, 0.01f, 2.24468f),

    // R1 --> 119
    glm::vec3(5.34241f, 0.01f, 2.26936f),

    // B2 --> 120
    glm::vec3(5.31185f, 0.01f, 2.28699f),

    // Q1 --> 121
    glm::vec3(5.27072f, 0.01f, 2.30815f),

    // 67 --> 122
    glm::vec3(5.21312f, 0.01f, 2.32696f),

    // S1 --> 123
    glm::vec3(5.14714f, 0.01f, 2.33111f),

    // T1 --> 124
    glm::vec3(5.06505f, 0.01f, 2.33426f),

    // 68 --> 125
    glm::vec3(4.99687f, 0.01f, 2.33241f),

    // 69 --> 126
    glm::vec3(4.71066f, 0.01f, 2.3181f),

    // 70 --> 127
    glm::vec3(4.32427f, 0.01f, 2.28947f),

    // 71 --> 128
    glm::vec3(3.82339f, 0.01f, 2.24654f),

    // 72 --> 129
    glm::vec3(3.32252f, 0.01f, 2.20361f),

    // 73 --> 130
    glm::vec3(2.7644f, 0.01f, 2.16068f),

    // 74 --> 131
    glm::vec3(2.16334f, 0.01f, 2.11775f),

    // 75 --> 132
    glm::vec3(1.67678f, 0.01f, 2.0605f),

    // 76 --> 133
    glm::vec3(1.29039f, 0.01f, 1.98895f),

    // 77 --> 134
    glm::vec3(0.904f, 0.01f, 1.87446f),

    // 78 --> 135
    glm::vec3(0.53192f, 0.01f, 1.74567f),

    // 79 --> 136
    glm::vec3(0.13122f, 0.01f, 1.58825f),

    // 80 --> 137
    glm::vec3(-0.25517f, 0.01f, 1.428f),

    // 81 --> 138
    glm::vec3(-0.65588f, 0.01f, 1.23048f),

    // 82 --> 139
    glm::vec3(-1, 0.01f, 1.095f),

    // 83 --> 140
    glm::vec3(-1.28555f, 0.01f, 0.9872f),

    // P2 --> 141
    glm::vec3(-1.4496f, 0.01f, 0.9554f),

    // 84 --> 142
    glm::vec3(-1.59874f, 0.01f, 0.9642f),

    // D2 --> 143
    glm::vec3(-1.74803f, 0.01f, 0.98236f),

    // 85 --> 144
    glm::vec3(-1.89045f, 0.01f, 1.01974f),

    // E2 --> 145
    glm::vec3(-2.02125f, 0.01f, 1.058f),

    // 86 --> 146
    glm::vec3(-2.14419f, 0.01f, 1.10168f),

    // F2 --> 147
    glm::vec3(-2.27918f, 0.01f, 1.1795f),

    // 87 --> 148
    glm::vec3(-2.40381f, 0.01f, 1.26677f),

    // G2 --> 149
    glm::vec3(-2.54526f, 0.01f, 1.38871f),

    // 88 --> 150
    glm::vec3(-2.66998f, 0.01f, 1.51537f),

    // H2 --> 151
    glm::vec3(-2.76706f, 0.01f, 1.66577f),

    // 89 --> 152
    glm::vec3(-2.83111f, 0.01f, 1.77429f),

    // I2 --> 153
    glm::vec3(-2.87431f, 0.01f, 1.87822f),

    // J2 --> 154
    glm::vec3(-2.90187f, 0.01f, 1.97105f),

    // K2 --> 155
    glm::vec3(-2.91416f, 0.01f, 2.05461f),

    // 90 --> 156
    glm::vec3(-2.92153f, 0.01f, 2.13817f),

    // L2 --> 157
    glm::vec3(-2.92871f, 0.01f, 2.23624f),

    // M2 --> 158
    glm::vec3(-2.93259f, 0.01f, 2.32549f),

    // N2 --> 159
    glm::vec3(-2.92289f, 0.01f, 2.40699f),

    // 91 --> 160
    glm::vec3(-2.90266f, 0.01f, 2.48983f),

    // O2 --> 161
    glm::vec3(-2.83691f, 0.01f, 2.64979f),

    // 92 --> 162
    glm::vec3(-2.70231f, 0.01f, 2.91915f),

    // 93 --> 163
    glm::vec3(-2.45903f, 0.01f, 3.17674f),

    // 94 --> 164
    glm::vec3(-2.20144f, 0.01f, 3.3914f),

    // 95 --> 165
    glm::vec3(-1.92953f, 0.01f, 3.57744f),

    // 96 --> 166
    glm::vec3(-1.68625f, 0.01f, 3.70624f),

    // 97 --> 167
    glm::vec3(-1.31417f, 0.01f, 3.84935f),

    // 98 --> 168
    glm::vec3(-0.99007f, 0.01f, 3.95614f),

    // 99 --> 169
    glm::vec3(-0.67019f, 0.01f, 4.02108f),

    // 100 --> 170
    glm::vec3(-0.35535f, 0.01f, 4.06401f),

    // 101 --> 171
    glm::vec3(0, 0.01f, 4.078f),

    // 102 --> 172
    glm::vec3(0.41743f, 0.01f, 4.07832f),

    // 103 --> 173
    glm::vec3(0.86107f, 0.01f, 4.09263f),

    // 104 --> 174
    glm::vec3(1.31901f, 0.01f, 4.09263f),

    // 105 --> 175
    glm::vec3(1.71186f, 0.01f, 4.07165f),

    // 106 --> 176
    glm::vec3(2.01068f, 0.01f, 4.02896f),

    // 107 --> 177
    glm::vec3(2.23417f, 0.01f, 3.96619f),

    // T2 --> 178
    glm::vec3(2.39488f, 0.01f, 3.88332f),

    // 108 --> 179
    glm::vec3(2.52111f, 0.01f, 3.80642f),

    // S2 --> 180
    glm::vec3(2.62841f, 0.01f, 3.70755f),

    // 109 --> 181
    glm::vec3(2.72634f, 0.01f, 3.59204f),

    // R2 --> 182
    glm::vec3(2.78912f, 0.01f, 3.47653f),

    // 110 --> 183
    glm::vec3(2.84397f, 0.01f, 3.36313f),

    // N3 --> 184
    glm::vec3(2.86211f, 0.01f, 3.33225f),

    // Q2 --> 185
    glm::vec3(2.8827f, 0.01f, 3.2975f),

    // L3 --> 186
    glm::vec3(2.90844f, 0.01f, 3.26147f),

    // M3 --> 187
    glm::vec3(2.93664f, 0.01f, 3.23219f),

    // O3 --> 188
    glm::vec3(2.9613f, 0.01f, 3.21264f),

    // P3 --> 189
    glm::vec3(2.99021f, 0.01f, 3.19648f),

    // 111 --> 190
    glm::vec3(3.02199f, 0.01f, 3.19105f),

    // U2 --> 191
    glm::vec3(3.16076f, 0.01f, 3.19277f),

    // 112 --> 192
    glm::vec3(3.329f, 0.01f, 3.20031f),

    // 113 --> 193
    glm::vec3(3.50478f, 0.01f, 3.22039f),

    // V2 --> 194
    glm::vec3(3.70064f, 0.01f, 3.24551f),

    // 114 --> 195
    glm::vec3(3.8714f, 0.01f, 3.29322f),

    // W2 --> 196
    glm::vec3(4.07479f, 0.01f, 3.36604f),

    // 115 --> 197
    glm::vec3(4.25308f, 0.01f, 3.44137f),

    // Z2 --> 198
    glm::vec3(4.3937f, 0.01f, 3.5167f),

    // 116 --> 199
    glm::vec3(4.53432f, 0.01f, 3.62468f),

    // A3 --> 200
    glm::vec3(4.63728f, 0.01f, 3.72512f),

    // 117 --> 201
    glm::vec3(4.72497f, 0.01f, 3.82073f),

    // B3 --> 202
    glm::vec3(4.82561f, 0.01f, 3.93103f),

    // Q3 --> 203
    glm::vec3(4.84678f, 0.01f, 3.95733f),

    // R3 --> 204
    glm::vec3(4.86817f, 0.01f, 3.98467f),

    // S3 --> 205
    glm::vec3(4.88434f, 0.01f, 4.00423f),

    // W3 --> 206
    glm::vec3(4.8968f, 0.01f, 4.01628f),

    // C3 --> 207
    glm::vec3(4.91632f, 0.01f, 4.01919f),

    // T3 --> 208
    glm::vec3(4.94067f, 0.01f, 4.02092f),

    // U3 --> 209
    glm::vec3(4.97335f, 0.01f, 4.02151f),

    // V3 --> 210
    glm::vec3(5.00247f, 0.01f, 4.02151f),

    // 118 --> 211
    glm::vec3(5.02901f, 0.01f, 4.02143f),

    // D3 --> 212
    glm::vec3(5.1646f, 0.01f, 4.02143f),

    // 119 --> 213
    glm::vec3(5.36047f, 0.01f, 4.02394f),

    // 120 --> 214
    glm::vec3(5.67435f, 0.01f, 4.02394f),

    // 121 --> 215
    glm::vec3(6.03093f, 0.01f, 4.02394f),

    // 122 --> 216
    glm::vec3(6.35988f, 0.01f, 4.00636f),

    // 123 --> 217
    glm::vec3(6.67032f, 0.01f, 3.96458f),

    // 124 --> 218
    glm::vec3(7, 0.01f, 3.9f),

    // 125 --> 219
    glm::vec3(7.2341f, 0.01f, 3.83572f),

    // 126 --> 220
    glm::vec3(7.47572f, 0.01f, 3.72296f),

    // 127 --> 221
    glm::vec3(7.71734f, 0.01f, 3.5941f),

    // 128 --> 222
    glm::vec3(7.92674f, 0.01f, 3.43302f),

    // 129 --> 223
    glm::vec3(8.0958f, 0.01f, 3.3134f),

    // Z3 --> 224
    glm::vec3(8.2f, 0.01f, 3.2f),

    // A4 --> 225
    glm::vec3(8.2561f, 0.01f, 3.12535f),

    // 130 --> 226
    glm::vec3(8.31333f, 0.01f, 3.03032f),

    // B4 --> 227
    glm::vec3(8.34645f, 0.01f, 2.97143f),

    // C4 --> 228
    glm::vec3(8.38995f, 0.01f, 2.89781f),

    // 131 --> 229
    glm::vec3(8.4301f, 0.01f, 2.82754f),

    // D4 --> 230
    glm::vec3(8.45954f, 0.01f, 2.76165f),

    // E4 --> 231
    glm::vec3(8.48305f, 0.01f, 2.6823f),

    // F4 --> 232
    glm::vec3(8.4948f, 0.01f, 2.61079f),

    // 132 --> 233
    glm::vec3(8.48892f, 0.01f, 2.54418f),

    // G4 --> 234
    glm::vec3(8.45856f, 0.01f, 2.49227f),

    // H4 --> 235
    glm::vec3(8.40762f, 0.01f, 2.43349f),

    // I4 --> 236
    glm::vec3(8.35766f, 0.01f, 2.39431f),

    // J4 --> 237
    glm::vec3(8.30805f, 0.01f, 2.35266f),

    // 133 --> 238
    glm::vec3(8.23634f, 0.01f, 2.29099f),

    // 134 --> 239
    glm::vec3(8.0f, 0.01f, 2.1f),

    // 135 --> 240
    glm::vec3(7.76566f, 0.01f, 1.91887f),

    // 136 --> 241
    glm::vec3(7.47572f, 0.01f, 1.72558f),

    // 137 --> 242
    glm::vec3(7.21799f, 0.01f, 1.53228f),

    // 138 --> 243
    glm::vec3(6.92805f, 0.01f, 1.29066f),

    // 139 --> 244
    glm::vec3(6.66701f, 0.01f, 1.07916f),

    // F5 --> 245
    glm::vec3(6.63754f, 0.01f, 1.05717f),

    // E5 --> 246
    glm::vec3(6.61585f, 0.01f, 1.03174f),

    // O4 --> 247
    glm::vec3(6.6f, 0.01f, 1.0f),

    // P4 --> 248
    glm::vec3(6.57317f, 0.01f, 0.93482f),

    // Q4 --> 249
    glm::vec3(6.56826f, 0.01f, 0.86857f),

    // 140 --> 250
    glm::vec3(6.57038f, 0.01f, 0.78774f),

    // R4 --> 251
    glm::vec3(6.58092f, 0.01f, 0.70795f),

    // S4 --> 252
    glm::vec3(6.6f, 0.01f, 0.6f),

    // 141 --> 253
    glm::vec3(6.61662f, 0.01f, 0.50799f),

    // C5 --> 254
    glm::vec3(6.63965f, 0.01f, 0.4194f),

    // D5 --> 255
    glm::vec3(6.668f, 0.01f, 0.31309f),

    // 142 --> 256
    glm::vec3(6.69635f, 0.01f, 0.22273f),

    // T4 --> 257
    glm::vec3(6.73419f, 0.01f, 0.14411f),

    // U4 --> 258
    glm::vec3(6.77442f, 0.01f, 0.06222f),

    // 143 --> 259
    glm::vec3(6.82614f, 0.01f, -0.02542f),

    // V4 --> 260
    glm::vec3(6.88074f, 0.01f, -0.09439f),

    // W4 --> 261
    glm::vec3(6.95689f, 0.01f, -0.16479f),

    // 144 --> 262
    glm::vec3(7.03735f, 0.01f, -0.22657f),

    // Z4 --> 263
    glm::vec3(7.13505f, 0.01f, -0.29266f),

    // 145 --> 264
    glm::vec3(7.28242f, 0.01f, -0.35234f),

    // A5 --> 265
    glm::vec3(7.38648f, 0.01f, -0.3803f),

    // B5 --> 266
    glm::vec3(7.5201f, 0.01f, -0.40185f),

    // 146 --> 267
    glm::vec3(7.65291f, 0.01f, -0.40067f),

    // 147 --> 268
    glm::vec3(7.99117f, 0.01f, -0.40067f),

    // 148 --> 269
    glm::vec3(8.44219f, 0.01f, -0.41678f),

    // 149 --> 270
    glm::vec3(8.97376f, 0.01f, -0.41678f),

    // L4 --> 271
    glm::vec3(9.0742f, 0.01f, -0.41435f),

    // M4 --> 272
    glm::vec3(9.17354f, 0.01f, -0.41727f),

    // 150 --> 273
    glm::vec3(9.30502f, 0.01f, -0.43188f),

    // N4 --> 274
    glm::vec3(9.42856f, 0.01f, -0.45302f),

    // K4 --> 275
    glm::vec3(9.56334f, 0.01f, -0.49345f),

    // 151 --> 276
    glm::vec3(9.71876f, 0.01f, -0.55558f),

    // K3 --> 277
    glm::vec3(9.90092f, 0.01f, -0.62823f),

    // 152 --> 278
    glm::vec3(10.05074f, 0.01f, -0.74353f),

    // J3 --> 279
    glm::vec3(10.16995f, 0.01f, -0.85541f),

    // 153 --> 280
    glm::vec3(10.25996f, 0.01f, -1.00504f),

    // I3 --> 281
    glm::vec3(10.31344f, 0.01f, -1.1065f),

    // P154 --> 282
    glm::vec3(10.34495f, 0.01f, -1.24041f),

    // H3 --> 283
    glm::vec3(10.36126f, 0.01f, -1.36955f),

    // P173 --> 284
    glm::vec3(10.35149f, 0.01f, -1.54769f),

    // G3 --> 285
    glm::vec3(10.31643f, 0.01f, -1.69837f),

    // 155 --> 286
    glm::vec3(10.23017f, 0.01f, -1.86649f),

    // F3 --> 287
    glm::vec3(10.08087f, 0.01f, -2.0511f),

    // 156 --> 288
    glm::vec3(9.90802f, 0.01f, -2.15643f),

    // E3 --> 289
    glm::vec3(9.71265f, 0.01f, -2.19615f),

    // 157 --> 290
    glm::vec3(9.50532f, 0.01f, -2.20476f),

    // 158 --> 291
    glm::vec3(9.0543f, 0.01f, -2.20476f),

    // 159 --> 292
    glm::vec3(8.50663f, 0.01f, -2.20476f),

    // 160 --> 293
    glm::vec3(7.97506f, 0.01f, -2.20476f),

    // 161 --> 294
    glm::vec3(7.37907f, 0.01f, -2.20476f),

    // 162 --> 295
    glm::vec3(6.79919f, 0.01f, -2.20476f),

    // 163 --> 296
    glm::vec3(6.07433f, 0.01f, -2.20476f),

    // 164 --> 297
    glm::vec3(5.59109f, 0.01f, -2.22086f),

    // 165 --> 298
    glm::vec3(4.89845f, 0.01f, -2.23697f),

    // 166 --> 299
    glm::vec3(4.15749f, 0.01f, -2.25308f),

    // 167 --> 300
    glm::vec3(3.54539f, 0.01f, -2.25308f),

    // 168 --> 301
    glm::vec3(3.02993f, 0.01f, -2.25308f),

    // 169 --> 302
    glm::vec3(2.48226f, 0.01f, -2.25308f),

    // 170 --> 303
    glm::vec3(1.93459f, 0.01f, -2.25308f),

    // 171 --> 304
    glm::vec3(1.48357f, 0.01f, -2.26919f),

    // 172 --> 305
    glm::vec3(0.91979f, 0.01f, -2.26919f)
};

int last_point = middle_positions.size() - 1;

glm::vec3 createObject::CalculateCoordinates(int basic_angle, int& current_angle, float radius) {
    float d_pi = 2 * M_PI;
    float x = radius * cos(current_angle * M_PI / 180);
    float y = radius * sin(current_angle * M_PI / 180);

    current_angle += basic_angle;

    return glm::vec3(x, y, 0);
}

glm::vec3 createObject::CalculateInnerOuterCoordinates(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int above, float distance) {
    if (above) {
        // d = p2 - p1;
        d1 = glm::normalize(p2 - p1);
        d2 = glm::normalize(p3 - p2);

        glm::vec3 n1 = glm::cross(d1, glm::vec3(0, 1, 0));
        glm::vec3 n2 = glm::cross(d1, glm::vec3(0, 1, 0));
        // p = glm::normalize(glm::cross(d, glm::vec3(0, 1, 0)));

        p = glm::normalize(n1 + n2);

        return p2 + distance * p;

    }

    return p2 - distance * p;
}

Mesh* createObject::CreateTree(
    const std::string& name,
    float height_trunk,
    float width_trunk,
    float length_trunk,
    float height_parallelipiped,
    float width_parallelipiped,
    float length_parallelipiped,
    float height_base,
    float width_base,
    float length_base,
    glm::vec3 color[4],
    bool fill)
{


    std::vector<VertexFormat> vertices =
    {
            // trunk
            VertexFormat(glm::vec3(-length_trunk / 2, 0, 0), color[0]), // 0
            VertexFormat(glm::vec3(length_trunk / 2, 0, 0), color[0]), // 1
            VertexFormat(glm::vec3(length_trunk / 2, 0, -width_trunk), color[0]), // 2
            VertexFormat(glm::vec3(-length_trunk / 2, 0, -width_trunk), color[0]), // 3
            VertexFormat(glm::vec3(-length_trunk / 2, height_trunk, 0), color[0]), // 4
            VertexFormat(glm::vec3(length_trunk / 2, height_trunk, 0), color[0]), // 5
            VertexFormat(glm::vec3(length_trunk / 2, height_trunk, -width_trunk), color[0]), // 6
            VertexFormat(glm::vec3(-length_trunk / 2, height_trunk, -width_trunk), color[0]), // 7

           // parallelipiped
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 8
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 9
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 10
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 11
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 12
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 13
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 14
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 15
    
           // base
            VertexFormat(glm::vec3(-length_base / 2, height_trunk, width_base / 2 - width_trunk / 2), color[2]), // 16
            VertexFormat(glm::vec3(length_base / 2, height_trunk, width_base / 2 - width_trunk / 2), color[2]), // 17
            VertexFormat(glm::vec3(length_base / 2, height_trunk, -width_base / 2 - width_trunk / 2), color[2]), // 18
            VertexFormat(glm::vec3(-length_base / 2, height_trunk, -width_base / 2 - width_trunk / 2), color[2]), // 19

           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[2]), // 20
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[2]), // 21
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[2]), // 22
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[2]), // 23
    
            // ceiling
           VertexFormat(glm::vec3(-length_base / 2, height_trunk + height_parallelipiped + height_base * 2, width_base / 2 - width_trunk / 2), color[3]), // 24
            VertexFormat(glm::vec3(length_base / 2, height_trunk + height_parallelipiped + height_base * 2, width_base / 2 - width_trunk / 2), color[3]), // 25
            VertexFormat(glm::vec3(length_base / 2, height_trunk + height_parallelipiped + height_base * 2, -width_base / 2 - width_trunk / 2), color[3]), // 26
            VertexFormat(glm::vec3(-length_base / 2, height_trunk + height_parallelipiped + height_base * 2, -width_base / 2 - width_trunk / 2), color[3]), // 27

            VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[3]), // 28
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[3]), // 29
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[3]), // 30
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[3]), // 31

    };

    Mesh* tree = new Mesh(name);
    std::vector<unsigned int> indices = { 
                                         // trunk
                                          3, 1, 0,
                                          3, 2, 1,
                                          5, 2, 1,
                                          5, 6, 2,
                                          4, 3, 7,
                                          4, 0, 3,
                                          7, 5, 4,
                                          7, 6, 5,
                                          4, 5, 1,
                                          4, 1, 0,
                                          7, 2, 6,
                                          7, 3, 2,

                                          // foliage
                                          11, 9, 8,
                                          11, 10, 9,
                                          13, 10, 9,
                                          13, 14, 10,
                                          12, 11, 15,
                                          12, 8, 11,
                                          15, 13, 12,
                                          15, 14, 13,
                                          12, 13, 9,
                                          12, 9, 8,
                                          15, 10, 14,
                                          15, 11, 10,

                                          // base
                                          19, 17, 16,
                                          19, 18, 17,
                                          21, 18, 17,
                                          21, 22, 18,
                                          20, 19, 23,
                                          20, 16, 19,
                                          20, 21, 17,
                                          20, 17, 16,
                                          23, 18, 22, 
                                          23, 19, 18,

                                          // ceiling
                                          27, 25, 24,
                                          27, 26, 25,
                                          25, 30, 29,
                                          25, 26, 30,
                                          24, 31, 27,
                                          24, 28, 31,
                                          24, 25, 29,
                                          24, 29, 28,
                                          27, 30, 26,
                                          27, 31, 30
    };

    if (!fill) {
        tree->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* createObject::CreateParallelipiped(
    const std::string& name,
    float height,
    float width,
    float length,
    glm::vec3 color,
    bool fill)
{
    

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-length / 2, 0, width / 2), color), // 0
        VertexFormat(glm::vec3(length / 2, 0, width / 2), color), // 1
        VertexFormat(glm::vec3(length / 2, 0, -width / 2), color), // 2
        VertexFormat(glm::vec3(-length / 2, 0, -width / 2), color), // 3
        VertexFormat(glm::vec3(-length / 2, height, width / 2), color), // 4
        VertexFormat(glm::vec3(length / 2, height, width / 2), color), // 5
        VertexFormat(glm::vec3(length / 2, height, -width / 2), color), // 6
        VertexFormat(glm::vec3(-length / 2, height, -width / 2), color) // 7
    };

    Mesh* parallelipiped = new Mesh(name);
    std::vector<unsigned int> indices = { 3, 1, 0,
                                          3, 2, 1,
                                          5, 2, 1,
                                          5, 6, 2,
                                          4, 3, 7,
                                          4, 0, 3,
                                          7, 5, 4,
                                          7, 6, 5,
                                          4, 5, 1,
                                          4, 1, 0,
                                          7, 2, 6,
                                          7, 3, 2
                                        };

    if (!fill) {
        parallelipiped->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    parallelipiped->InitFromData(vertices, indices);
    return parallelipiped;
}

Mesh* createObject::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    float initial_x = corner.x;

    int nr_squares = 500;

    float small_side = length / nr_squares;
    int nr_indices_small_square = 6;
    int current_index = 0;

    for (int i = 0; i < nr_squares; i++) {
        for (int j = 0; j < nr_squares; j++) {
            vertices.push_back(VertexFormat(corner, color));
            vertices.push_back(VertexFormat(corner + glm::vec3(small_side, 0, 0), color));
            vertices.push_back(VertexFormat(corner + glm::vec3(small_side, small_side, 0), color));
            vertices.push_back(VertexFormat(corner + glm::vec3(0, small_side, 0), color));

            indices.push_back(current_index);
            indices.push_back(current_index + 1);
            indices.push_back(current_index + 2);

            indices.push_back(current_index);
            indices.push_back(current_index + 2);
            indices.push_back(current_index + 3);

            corner.x += small_side;
            current_index += 4;
        }

        corner.x = initial_x;
        corner.y += small_side;
    }

    Mesh* square = new Mesh(name);

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* createObject::CreateRectangle(
    const std::string& name,
    float height,
    float width,
    glm::vec3 center,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        // VertexFormat(glm::vec3(0, 0, 0), color), // 0
        // VertexFormat(glm::vec3(0, height, 0), color), // 1
        // VertexFormat(glm::vec3(width, height, 0), color), // 2
        // VertexFormat(glm::vec3(width, 0, 0), color) // 3

        VertexFormat(center + glm::vec3(-width / 2, -height / 2, 0), color), // 0
        VertexFormat(center + glm::vec3(-width / 2, height / 2, 0), color), // 1
        VertexFormat(center + glm::vec3(width / 2, height / 2, 0), color), // 2
        VertexFormat(center + glm::vec3(width / 2, -height / 2, 0), color) // 3
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3};

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* createObject::CreateCheckers(
    const std::string& name,
    float height,
    float width,
    int nr_columns,
    int nr_lines,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = glm::vec3(0, 0, 0);

    float small_side = height / nr_lines;
    int nr_indices_small_square = 6;
    int current_index = 0;

    std::vector<unsigned int> indices;
    std::vector<VertexFormat> vertices;

    float initial_x = corner.x;

    // glm::vec3 prev_color = color1;
    glm::vec3 current_color = color1;
    glm::vec3 start_color = color1;

    for (int i = 0; i < nr_lines; i++) {
        for (int j = 0; j < nr_columns; j++) {
            vertices.push_back(VertexFormat(corner, current_color));
            vertices.push_back(VertexFormat(corner + glm::vec3(small_side, 0, 0), current_color));
            vertices.push_back(VertexFormat(corner + glm::vec3(small_side, small_side, 0), current_color));
            vertices.push_back(VertexFormat(corner + glm::vec3(0, small_side, 0), current_color));

            indices.push_back(current_index);
            indices.push_back(current_index + 1);
            indices.push_back(current_index + 2);

            indices.push_back(current_index);
            indices.push_back(current_index + 2);
            indices.push_back(current_index + 3);

            corner.x += small_side;
            current_index += 4;

            if (current_color == color1) {
                current_color = color2;
            }
            else {
                current_color = color1;
            }
        }

        corner.x = initial_x;
        corner.y += small_side;

        if (start_color == color1) {
            start_color = color2;
            current_color = color2;
        }
        else {
            start_color = color1;
            current_color = color1;
        }
    }

    Mesh* rectangle = new Mesh(name);

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* createObject::CreateTriangle(
    const std::string& name,
    float height,
    float base_part1,
    float base_part2,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, height, 0), color),
        VertexFormat(glm::vec3(base_part1 , 0, 0), color),
        VertexFormat(glm::vec3(base_part2, 0, 0), color)

    };

    std::vector<unsigned int> indices =
    {
        1, 2, 0
    };

    Mesh* triangle = new Mesh(name);

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* createObject::CreateCircle(
    const std::string& name,
    float radius,
    glm::vec3 color,
    bool fill)
{

    int angle = 10;
    int current_angle = 0;

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0, 0), color), // 0
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 1
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 2
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 3
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 4
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 5
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 6
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 7
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 8
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 9
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 10
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 11
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 12
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 13
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 14
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 15
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 16
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 17
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 18
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 19
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 20
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 21
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 22
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 23
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 24
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 25
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 26
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 27
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 28
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 29
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 30
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 31
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 32
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 33
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 34
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 35
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 36
    };

    std::vector<unsigned int> indices =
    {
        1, 2, 0,
        2, 3, 0,
        3, 4, 0,
        4, 5, 0,
        5, 6, 0,
        6, 7, 0,
        7, 8, 0,
        8, 9, 0,
        9, 10, 0,
        10, 11, 0,
        11, 12, 0,
        12, 13, 0,
        13, 14, 0,
        14, 15, 0,
        15, 16, 0,
        16, 17, 0,
        17, 18, 0,
        18, 19, 0,
        19, 20, 0,
        20, 21, 0,
        21, 22, 0,
        22, 23, 0,
        23, 24, 0,
        24, 25, 0,
        25, 26, 0,
        26, 27, 0,
        27, 28, 0,
        28, 29, 0,
        29, 30, 0,
        30, 31, 0,
        31, 32, 0,
        32, 33, 0,
        33, 34, 0,
        34, 35, 0,
        35, 36, 0,
        36, 1, 0
    };

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* createObject::CreateRaceTrack(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    float distance1 = 0.05f;
    float distance2 = 0.1f;
    float distance3 = 0.15f;
    float distance4 = 0.2f;
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < middle_positions.size() - 2; i++) {
        vertices.push_back(VertexFormat(middle_positions[i + 1], color)); // 0

        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 1, distance1), color)); // 1
        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 0, distance1), color)); // 2

        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 1, distance2), color)); // 3
        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 0, distance2), color)); // 4

        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 1, distance3), color)); // 5
        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 0, distance3), color)); // 6

        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 1, distance4), color)); // 7
        vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 0, distance4), color)); // 8

        racetrack_margins.push_back(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 1, distance4));
        racetrack_margins.push_back(CalculateInnerOuterCoordinates(middle_positions[i], middle_positions[i + 1], middle_positions[i + 2], 0, distance4));
    }

    vertices.push_back(VertexFormat(middle_positions[last_point], color)); // 0

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 1, distance1), color)); // 1
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 0, distance1), color)); // 2

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 1, distance2), color)); // 3
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 0, distance2), color)); // 4

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 1, distance3), color)); // 5
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 0, distance3), color)); // 6

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 1, distance4), color)); // 7
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 0, distance4), color)); // 8

    racetrack_margins.push_back(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 1, distance4));
    racetrack_margins.push_back(CalculateInnerOuterCoordinates(middle_positions[last_point - 1], middle_positions[last_point], middle_positions[0], 0, distance4));


    vertices.push_back(VertexFormat(middle_positions[0], color)); // 0

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 1, distance1), color)); // 1
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 0, distance1), color)); // 2

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 1, distance2), color)); // 3
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 0, distance2), color)); // 4

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 1, distance3), color)); // 5
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 0, distance3), color)); // 6

    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 1, distance4), color)); // 7
    vertices.push_back(VertexFormat(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 0, distance4), color)); // 8

    racetrack_margins.push_back(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 1, distance4));
    racetrack_margins.push_back(CalculateInnerOuterCoordinates(middle_positions[last_point], middle_positions[0], middle_positions[1], 0, distance4));

    std::vector<unsigned int> indices;

    int starting_index, next_index;

    for (int i = 0; i < middle_positions.size(); i++) {
        if (i != last_point) {
            starting_index = i * 9;
            next_index = (i + 1) * 9;
        }
        else {
            starting_index = i * 9;
            next_index = 0;
        }

        indices.push_back(starting_index);
        indices.push_back(next_index + 1);
        indices.push_back(next_index);

        indices.push_back(starting_index);
        indices.push_back(starting_index + 1);
        indices.push_back(next_index + 1);

        indices.push_back(starting_index + 1);
        indices.push_back(next_index + 3);
        indices.push_back(next_index + 1);

        indices.push_back(starting_index + 1);
        indices.push_back(starting_index + 3);
        indices.push_back(next_index + 3);

        indices.push_back(starting_index + 3);
        indices.push_back(next_index + 5);
        indices.push_back(next_index + 3);

        indices.push_back(starting_index + 3);
        indices.push_back(starting_index + 5);
        indices.push_back(next_index + 5);

        indices.push_back(starting_index + 5);
        indices.push_back(next_index + 7);
        indices.push_back(next_index + 5);

        indices.push_back(starting_index + 5);
        indices.push_back(starting_index + 7);
        indices.push_back(next_index + 7);


        indices.push_back(starting_index);
        indices.push_back(next_index);
        indices.push_back(starting_index + 2);

        indices.push_back(starting_index + 2);
        indices.push_back(next_index);
        indices.push_back(next_index + 2);

        indices.push_back(starting_index + 2);
        indices.push_back(next_index + 2);
        indices.push_back(starting_index + 4);

        indices.push_back(starting_index + 4);
        indices.push_back(next_index + 2);
        indices.push_back(next_index + 4);

        indices.push_back(starting_index + 4);
        indices.push_back(next_index + 4);
        indices.push_back(starting_index + 6);

        indices.push_back(starting_index + 6);
        indices.push_back(next_index + 4);
        indices.push_back(next_index + 6);

        indices.push_back(starting_index + 6);
        indices.push_back(next_index + 6);
        indices.push_back(starting_index + 8);

        indices.push_back(starting_index + 8);
        indices.push_back(next_index + 6);
        indices.push_back(next_index + 8);
    }

    Mesh* raceTrack = new Mesh(name);

    if (!fill) {
        raceTrack->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    raceTrack->InitFromData(vertices, indices);
    return raceTrack;
}

std::vector<glm::vec3> createObject::getPositions(float distance, std::vector<glm::vec3> positions) {

    std::vector<glm::vec3> vertices;
    int last = positions.size() - 1;

    for (int i = 0; i < positions.size() - 2; i++) {
        vertices.push_back(CalculateInnerOuterCoordinates(positions[i], positions[i + 1], positions[i + 2], 1, distance));
        vertices.push_back(CalculateInnerOuterCoordinates(positions[i], positions[i + 1], positions[i + 2], 0, distance));
    }

    vertices.push_back(CalculateInnerOuterCoordinates(positions[last - 1], positions[last], positions[0], 1, distance));
    vertices.push_back(CalculateInnerOuterCoordinates(positions[last - 1], positions[last], positions[0], 0, distance));


    vertices.push_back(CalculateInnerOuterCoordinates(positions[last], positions[0], positions[1], 1, distance));
    vertices.push_back(CalculateInnerOuterCoordinates(positions[last], positions[0], middle_positions[1], 0, distance));

    return vertices;
}

std::vector<glm::vec3> createObject::getMiddlePositions() {
    return middle_positions;
}

std::vector<glm::vec3> createObject::getRaceTrackMargins() {
    return racetrack_margins;
}

std::vector<glm::vec3> createObject::getTreePositions() {
    std::vector<glm::vec3> treePositions;

    for (int i = 0; i <= 13; i++) {
        treePositions.push_back(middle_positions[i]); // up to 13
    }

    treePositions.push_back(middle_positions[15]); // 14
    treePositions.push_back(middle_positions[18]); // 15

    for (int i = 21; i <= 35; i++) {
        treePositions.push_back(middle_positions[i]); // up to 30
    }

     treePositions.push_back(middle_positions[38]); // 31
     treePositions.push_back(middle_positions[43]); // 32
     treePositions.push_back(middle_positions[48]); // 33
     treePositions.push_back(middle_positions[53]); // 34
     treePositions.push_back(middle_positions[57]); // 35
     treePositions.push_back(middle_positions[75]);

    for (int i = 76; i <= 109; i++) {
        treePositions.push_back(middle_positions[i]); // up to 68
    }

    treePositions.push_back(middle_positions[117]); // problem in interior  // 69
    treePositions.push_back(middle_positions[122]); // pb in interior       // 70

    for (int i = 125; i <= 140; i++) {
        treePositions.push_back(middle_positions[i]); // up to 86
    }

    treePositions.push_back(middle_positions[142]);  // 87
    treePositions.push_back(middle_positions[144]);  // 88
    treePositions.push_back(middle_positions[146]);  // 89
    treePositions.push_back(middle_positions[148]);  // 90
    treePositions.push_back(middle_positions[150]);  // 91
    treePositions.push_back(middle_positions[152]);  // 92
    treePositions.push_back(middle_positions[154]);  // 93
    treePositions.push_back(middle_positions[156]);  // 94
    treePositions.push_back(middle_positions[158]);  // 95
    treePositions.push_back(middle_positions[160]);  // 96
    treePositions.push_back(middle_positions[161]);  // 97
    treePositions.push_back(middle_positions[162]);  // 98

    for (int i = 163; i <= 183 - 8; i++) {
        treePositions.push_back(middle_positions[i]); // up to 111
    }

    for (int i = 183 - 6; i <= 183; i += 2) {
        treePositions.push_back(middle_positions[i]); // up to 118
    }

    treePositions.push_back(middle_positions[190]); // 119
    treePositions.push_back(middle_positions[192]); // 120

    for (int i = 194; i <= 201; i++) {
        treePositions.push_back(middle_positions[i]); // pana la 128
    }

    treePositions.push_back(middle_positions[207]); // 129
    treePositions.push_back(middle_positions[210]); // 130
    treePositions.push_back(middle_positions[212]); // 132
    treePositions.push_back(middle_positions[213]); // 133
    treePositions.push_back(middle_positions[214]); // 134
    treePositions.push_back(middle_positions[215]); // 135
    treePositions.push_back(middle_positions[216]); // 136

    for (int i = 217; i <= 222; i++) {
        treePositions.push_back(middle_positions[i]); // up to 142
    }

    treePositions.push_back(middle_positions[224]); // 143
    treePositions.push_back(middle_positions[226]); // 144
    treePositions.push_back(middle_positions[228]); // 145
    treePositions.push_back(middle_positions[230]); // 146
    treePositions.push_back(middle_positions[234]); // 149
    treePositions.push_back(middle_positions[238]); // 151

    for (int i = 239; i <= 243; i++) {
        treePositions.push_back(middle_positions[i]); // up to 157
    }

    treePositions.push_back(middle_positions[248]); // up to 158
    treePositions.push_back(middle_positions[252]); // up to 160
    treePositions.push_back(middle_positions[256]); // up to 162
    treePositions.push_back(middle_positions[258]); // up to 163
    treePositions.push_back(middle_positions[260]); // up to 164
    treePositions.push_back(middle_positions[262]); // up to 165
    treePositions.push_back(middle_positions[264]); // up to 166
    treePositions.push_back(middle_positions[267]); // up to 167
    treePositions.push_back(middle_positions[268]); // up to 168
    treePositions.push_back(middle_positions[269]); // up to 169
    treePositions.push_back(middle_positions[270]); // up to 170

    for (int i = 270; i < middle_positions.size(); i++) {
        treePositions.push_back(middle_positions[i]); // up to 206
    }

    return treePositions;
}