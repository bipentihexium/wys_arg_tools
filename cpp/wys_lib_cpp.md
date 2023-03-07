# wys_lib.hpp

- [wys\_lib.hpp](#wys_libhpp)
	- [Data](#data)
	- [Decrypt/encrypt functions](#decryptencrypt-functions)

## Data

There are `data1`, ..., `data5` containing all data we got so far, `text1`, ..., `text5` containing all texts we got so far, `hint1`, ..., `hint5` containing all "hints" contained in the texts we got so far, `key2`, ... `key4` containing all keys we found and needed so far and then `hint3decrypted`, `hint4decrypted`. All of them are defined as `constexpr const char *`.

## Decrypt/encrypt functions

There are three pairs of decrypt and encrypt functions: `dontbother17_decrypt/encrypt`, `humanscantsolvethis_decrypt/encrypt` an `intelligencecheck_decrypt/encrypt`. The first one - `dontbother17_decrypt/encrypt` implement the [dontbother algorithm](solutions.md#level-1). They both take data and N (key) (which defaults to `17`), and return the decrypted/encrypted text. `humanscantsolvethis_decrypt/encrypt` implement the [humanscantsolvethis algorithm](solutions.md#level-2) and take data and key (which defaults to `"HUMANSCANTSOLVETHISSOBETTERSTOPHERE"`). `intelligencecheck_decrypt/encrypt` are same as `humanscantsolvethis_decrypt/encrypt`, but they take begin and end iterators to  skips instead of the key.
