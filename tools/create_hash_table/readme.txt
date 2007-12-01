create_hash_table is a qt based replacement for the similar perl script located in kdelibs/kjs. 

This tool is used to generate the lexer keyword hash table located in 
kdesdk/umbrello/umbrello/codeimport/kdevcppparser/keywords.lut.h on windows. 

Extending the hash table is required to support additional languages for example php. 

This tool is only partially able to create the hash tables used in kdelibs/kjs, 
it is only able to create lexer.lut.h at now. To become a full replacement off the perl 
implementation and to kick of the perl script it has to be extended to be able to create 
the kdelibs/kjs/..._object.lut.h files. 




