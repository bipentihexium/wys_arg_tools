# wys_lib.h

- [wys\_lib.h](#wys_libh)
	- [Data](#data)
	- [Decrypt/encrypt functions](#decryptencrypt-functions)

## Data

There are `DATA1`, ..., `DATA5` containing all data we got so far, `TEXT1`, ..., `TEXT5` containing all texts we got so far, `HINT1`, ..., `HINT5` containing all "hints" contained in the texts we got so far, `KEY2`, ... `KEY4` containing all keys we found and needed so far and then `HINT3_DECRYPTED`, `HINT4_DECRYPTED`. All of them are macros.

## Decrypt/encrypt functions

There are three pairs of decrypt and encrypt functions: `dontbother17_decrypt/encrypt`, `humanscantsolvethis_decrypt/encrypt` an `intelligencecheck_decrypt/encrypt`. The first one - `dontbother17_decrypt/encrypt` implement the [dontbother algorithm](solutions.md#level-1). They both take data, data length, n (key), and output pointer. They output the decrypted/encrypted text into out. `humanscantsolvethis_decrypt/encrypt` implement the [humanscantsolvethis algorithm](solutions.md#level-2), They are the same as dontbother functions, but instead of n they take pointer to key and key length. `intelligencecheck_decrypt/encrypt` are same as `humanscantsolvethis_decrypt/encrypt`, but they key is made from `unsigned int`s - numbers, instead of `char`s - letters ("ABC...").
