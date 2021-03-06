
/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * MAM is based on an original implementation & specification by apmi.bsu.by
 [ITSec Lab]

 *
 *
 * Refer to the LICENSE file for licensing information
 */

/*!
\file buffers.c
\brief Trits collection to simplify buffered operations.
*/
#include "mam/v2/buffers.h"

MAM2_SAPI MAM2_INLINE buffers_t buffers_init(size_t n, trits_t *Xs) {
  buffers_t bs = {trits_null(), n, Xs};
  return bs;
}

MAM2_SAPI MAM2_INLINE bool_t buffers_is_empty(buffers_t bs) {
  return trits_is_empty(bs.X) && (0 == bs.n);
}

MAM2_SAPI size_t buffers_size(buffers_t bs) {
  size_t m = 0;

  for (; !buffers_is_empty(bs);) {
    m += trits_size(bs.X);
    bs.X = trits_null();

    if (0 < bs.n) {
      bs.X = *bs.Xs++;
      bs.n--;
    }
  }

  return m;
}

MAM2_SAPI size_t buffers_copy_to(buffers_t *bs, trits_t buf) {
  size_t k, m = 0;

  for (; !trits_is_empty(buf) && !buffers_is_empty(*bs);) {
    k = trits_copy_min(bs->X, buf);
    bs->X = trits_drop(bs->X, k);
    buf = trits_drop(buf, k);
    m += k;

    if (trits_is_empty(bs->X) && (0 < bs->n)) {
      bs->X = *bs->Xs++;
      bs->n--;
    }
  }

  return m;
}

MAM2_SAPI size_t buffers_copy_from(buffers_t *bs, trits_t buf) {
  size_t k, m = 0;

  for (; !trits_is_empty(buf) && !buffers_is_empty(*bs);) {
    k = trits_copy_min(buf, bs->X);
    bs->X = trits_drop(bs->X, k);
    buf = trits_drop(buf, k);
    m += k;

    if (trits_is_empty(bs->X) && (0 < bs->n)) {
      bs->X = *bs->Xs++;
      bs->n--;
    }
  }

  return m;
}
