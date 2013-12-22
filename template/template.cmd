/* template.cmd : generate template sources for KPMLib */

CALL RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs';
CALL SysLoadFuncs;

PARSE ARG sProgName sDestDir;

IF sProgName = '' THEN
DO
    SAY 'Usage: template[.cmd] prog-name [dest-dir]';
    EXIT(1);
END

sUpperName = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
sLowerName = 'abcdefghijklmnopqrstuvwxyz';

sProgUpperName = TRANSLATE(sProgName, sUpperName, sLowerName);
sProgLowerName = TRANSLATE(sProgName, sLowerName, sUpperName);

TemplateList.1 = 'template.cpp';
TemplateList.2 = 'template.h';
TemplateList.3 = 'templateClient.cpp';
TemplateList.4 = 'templateClient.h';
TemplateList.5 = 'template.def';
TemplateList.6 = 'Makefile.template';
TemplateList.7 = 'Makefile.common';
TemplateList.0 = 7;

IF sDestDir = '' THEN
    sDestDir = sProgName;

rc = SysFileTree(sDestDir, DirList);
IF (rc = 0) & (DirList.0 = 0) THEN
    CALL SysMkDir(sDestDir);
ELSE
   sDestDir = sProgName;

sDestDir = sDestDir || '\';

GenList.1 = sDestDir || sProgName || '.cpp';
GenList.2 = sDestDir || sProgName || '.h';
GenList.3 = sDestDir || sProgName || 'Client.cpp';
GenList.4 = sDestDir || sProgName || 'Client.h';
GenList.5 = sDestDir || sProgName || '.def';
GenList.6 = sDestDir || 'Makefile';
GenList.7 = sDestDir || 'Makefile.common';
GenList.0 = 7;

DO nI = 1 to TemplateList.0
    ADDRESS CMD 'sed -e s/@PROG_NAME@/' || sProgName || '/g ' ||,
                    '-e s/@PROG_UPPER_NAME@/' || sProgUpperName || '/g ' ||,
                    '-e s/@PROG_LOWER_NAME@/' || sProgLowerName || '/g ' ||,
                '<' || TemplateList.nI || '>' || GenList.nI;
END

EXIT(0);
