It contains:  
`text1`, `text2`, ... `text5` - message (with data) for each level  
`data1`, `data2`, ... `data5` - data for each level  
`hint1`, `hint2`, ... `hint5` - hint for each level  
`hint3decrypted`, `hint4decrypted` - decrypted versions of hints for levels 3 (reverse) and 4 (solved acronyms)  
`key2`, `key3`, `key4` - keys for levels 2, 3 and 4  
`uppercase` - just uppercase alphabet (because `UPPERCASE` in L4 hint)  
`dontbother17_decrypt(data, n=17)` and `dontbother17_encrypt(data, n=17)` - functions to decrypt/encrypt data using the dontbother method; n is the step size (17 for dontbother17)  
`humanscantsolvethis_decrypt(data, key="HUMANSCANTSOLVETHISSOBETTERSTOPHERE")` and `humanscantsolvethis_encrypt(data, key="HUMANSCANTSOLVETHISSOBETTERSTOPHERE")` - functions to decrypt/encrypt data using the humanscantsolvethis... method  
`sheismymother_decrypt(data, key="EILLE")` and `sheismymother_encrypt(data, key="EILLE")` - just lambdas calling `humanscantsolvethis_decrypt`/`encrypt` as L3 used the same algotithm as L2; only the key defaults are different  
`dontbother17_gen`, `humanscantsolvethis_gen`, `sheismymother_gen` - permutation generators (returns list containing the permutation) for each method (arguments same as for the `decrypt`/`encrypt` functions)  
`TranspositionCipher` - class for permutation fun :)  
`TranspositionCipher.__init__(self, data, generator=None, *args)` - TC constructor, generator is permutation generator, which is called with `generator(data,*args)`. If the generator is `None` (default), then the permutation will be identity.  
`TranspositionCipher.from_perm(cls, data, perm)` (class method) - creates TC from data and permutation list  
`TranspositionCipher.data` - gets TC data  
`TranspositionCipher.perm` - permutation contained in the TC  
`TranspositionCipher.len` - length of TC data  
`TranspositionCipher.identity_perm(self)` - makes a new identity permutation list (with length `len`)  
`TranspositionCipher.identity(self)` - makes a new identity TC  
`TranspositionCipher.apply_on(self, arr)` - applies the permutation to the `arr` (`arr` can be any iterable, it returns string for string `arr` and list for all other types)  
`TranspositionCipher.apply(self)` - applies the permutation to contained `data`  
`TranspositionCipher.__invert__(self)` (`~tc`) - returns a new TC with inversed permutation (`~tc(tc(x)) == x`)  
`TranspositionCipher.__mul__(self, cipher_b)` (`tca * tcb`) - returns a new TC with combined permutation (`(tca * tcb)(x) == tca(tcb(x))`)  
`TranspositionCipher.__pow__(self, n)` (`tc ** n` (`n` is an integer)) - returns a new TC with some power of the permutation (`tc ** n == ~tc ** -n`, `tc ** 0 == identity`, `tc ** n == tc * tc * tc ... tc` (`tc is there n times`))  
`mask_data(data, shown_chars, mask_char='.')` - masks out characters, which are not in `shown_chars`, with `mask_char` from `data`  
`humanscantsolvethis_keys_from_result(data, result, offets)` - returns a list of keys for L2 algorithm which make result at any of the offsets  
`humanscantsolvethis_keys_from_condition(data, cond, length, offets)` - returns a list of keys for L2 algorithm which make a string of length `length` where all characters obey `cond` at any of the offsets