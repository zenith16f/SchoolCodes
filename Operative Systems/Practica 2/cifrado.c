// Include
#include "login.h"
#include <stdint.h>

// Bit Operations del algoritmo
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define EP1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))

// Constantes K del algoritmo
static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// Struct
typedef struct {
  uint8_t datos[64];
  uint32_t longitud_datos;
  uint64_t longitud_bits;
  uint32_t estado[8];
} SHA256_CTX;

// Functions
static void sha256Transformar(SHA256_CTX *ctx, const uint8_t datos[]) {
  uint32_t a, b, c, d, e, f, g, h, t1, t2, w[64];
  int i;

  for (i = 0; i < 16; i++)
    w[i] = ((uint32_t)datos[i * 4] << 24) | ((uint32_t)datos[i * 4 + 1] << 16) |
           ((uint32_t)datos[i * 4 + 2] << 8) | ((uint32_t)datos[i * 4 + 3]);

  for (i = 16; i < 64; i++)
    w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];

  a = ctx->estado[0];
  b = ctx->estado[1];
  c = ctx->estado[2];
  d = ctx->estado[3];
  e = ctx->estado[4];
  f = ctx->estado[5];
  g = ctx->estado[6];
  h = ctx->estado[7];

  for (i = 0; i < 64; i++) {
    t1 = h + EP1(e) + CH(e, f, g) + K[i] + w[i];
    t2 = EP0(a) + MAJ(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + t1;
    d = c;
    c = b;
    b = a;
    a = t1 + t2;
  }

  ctx->estado[0] += a;
  ctx->estado[1] += b;
  ctx->estado[2] += c;
  ctx->estado[3] += d;
  ctx->estado[4] += e;
  ctx->estado[5] += f;
  ctx->estado[6] += g;
  ctx->estado[7] += h;
}

static void sha256Init(SHA256_CTX *ctx) {
  ctx->longitud_datos = 0;
  ctx->longitud_bits = 0;

  ctx->estado[0] = 0x6a09e667;
  ctx->estado[1] = 0xbb67ae85;
  ctx->estado[2] = 0x3c6ef372;
  ctx->estado[3] = 0xa54ff53a;
  ctx->estado[4] = 0x510e527f;
  ctx->estado[5] = 0x9b05688c;
  ctx->estado[6] = 0x1f83d9ab;
  ctx->estado[7] = 0x5be0cd19;
}

static void sha256Update(SHA256_CTX *ctx, const uint8_t datos[], size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    ctx->datos[ctx->longitud_datos] = datos[i];
    ctx->longitud_datos++;
    if (ctx->longitud_datos == 64) {
      sha256Transformar(ctx, ctx->datos);
      ctx->longitud_bits += 512;
      ctx->longitud_datos = 0;
    }
  }
}

static void sha256Final(SHA256_CTX *ctx, uint8_t hash[]) {
  uint32_t i = ctx->longitud_datos;

  ctx->datos[i++] = 0x80;
  if (ctx->longitud_datos < 56) {
    while (i < 56)
      ctx->datos[i++] = 0x00;
  } else {
    while (i < 64)
      ctx->datos[i++] = 0x00;
    sha256Transformar(ctx, ctx->datos);
    memset(ctx->datos, 0, 56);
  }

  ctx->longitud_bits += ctx->longitud_datos * 8;
  ctx->datos[63] = (uint8_t)(ctx->longitud_bits);
  ctx->datos[62] = (uint8_t)(ctx->longitud_bits >> 8);
  ctx->datos[61] = (uint8_t)(ctx->longitud_bits >> 16);
  ctx->datos[60] = (uint8_t)(ctx->longitud_bits >> 24);
  ctx->datos[59] = (uint8_t)(ctx->longitud_bits >> 32);
  ctx->datos[58] = (uint8_t)(ctx->longitud_bits >> 40);
  ctx->datos[57] = (uint8_t)(ctx->longitud_bits >> 48);
  ctx->datos[56] = (uint8_t)(ctx->longitud_bits >> 56);
  sha256Transformar(ctx, ctx->datos);

  for (i = 0; i < 4; i++) {
    hash[i] = (ctx->estado[0] >> (24 - i * 8)) & 0xff;
    hash[i + 4] = (ctx->estado[1] >> (24 - i * 8)) & 0xff;
    hash[i + 8] = (ctx->estado[2] >> (24 - i * 8)) & 0xff;
    hash[i + 12] = (ctx->estado[3] >> (24 - i * 8)) & 0xff;
    hash[i + 16] = (ctx->estado[4] >> (24 - i * 8)) & 0xff;
    hash[i + 20] = (ctx->estado[5] >> (24 - i * 8)) & 0xff;
    hash[i + 24] = (ctx->estado[6] >> (24 - i * 8)) & 0xff;
    hash[i + 28] = (ctx->estado[7] >> (24 - i * 8)) & 0xff;
  }
}

// Public Function
void Sha256String(const char *entrada, char *salida) {
  SHA256_CTX ctx;
  uint8_t hash[32];
  int i;

  sha256Init(&ctx);
  sha256Update(&ctx, (const uint8_t *)entrada, strlen(entrada));
  sha256Final(&ctx, hash);

  for (i = 0; i < 32; i++)
    sprintf(salida + (i * 2), "%02x", hash[i]);
  salida[64] = '\0';
}
