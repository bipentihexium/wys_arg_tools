# wys_indextable.py

This script will find all occurences of characters inside string and will print them in a table. It will ask you for data and string at runtime. It also prints possible keys for HCSTSBSH decryption starting at offsets between `0` and `200`. (warning, there can be lots of them, so I'd recommend redirecting the output into a file).
example input/output:
```
Data (default lvl5 data)>
String you want to find >fifth
f   i   f   t   h  
52  21  52  8   41  
69  24  69  20  106 
82  51  82  23  284 
135 80  135 44  330 
376 99  376 67  341 
    120     90  352 
    136     93  387 
    138     94  391 
    156     111     
    168     113     
    182     124     
    184     154     
    203     179     
    271     198     
    286     220     
    343     233     
    353     256     
            273     
            310     
            323     
            325     
            336     
            366     
            381     
            385     
 ------------------------------------------------ 
AJAKK; AJAJL; AJAGO; BJAKK; BJAJL; BJAGO; CJAKK; CJAJL; CJAGO; DJAKK; DJAJL; DJAGO; EJAKK; EJAJL; EJAGO; FJAKK; FJAJL; FJAGO; GJAKK; GJAJL; GJAGO; HJAKK; HJAJL; HJAGO; IJAKK; IJAJL; IJAGO; JJAKK; JJAJL; JJAGO; KJAKK; KJAJL; KJAGO; LJAKK; LJAJL; LJAGO; MJAKK; MJAJL; MJAGO; NJAKK; NJAJL; NJAGO; OJAKK; OJAJL; OJAGO; PJAKK; PJAJL; PJAGO; QJAKK; QJAJL; QJAGO; RJAKK; RJAJL; RJAGO; SJAKK; SJAJL; SJAGO; TJAKK; TJAJL; TJAGO; UJAKK; UJAJL; UJAGO; VJAKK; VJAJL; VJAGO; WJAKK; WJAJL; WJAGO; XJAKK; XJAJL; XJAGO; YJAKK; YJAJL; YJAGO; ZJAKK; ZJAJL; ZJAGO;
```
