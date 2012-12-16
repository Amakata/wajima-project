-----
Unittest Multilingual Integrated Generation & Maintenance Environment
                                                          with XML
���j�b�g�e�X�g�}���`����Ή������������e�i���X���uX�C�T�v������'umix'
-----

X�C�T'umix'��xUnit�ɂ�郆�j�b�g�e�X�g���x������c�[���ł��B
umix��xUnit�𗘗p�����e�X�g�̐��`�𐶐����܂��B�܂����\�b�h��ǉ����邱�Ƃ��ł��܂��B

���\�[�X�ŃC���X�g�[���̎d��

$DOWNLOAD_DIR/python/umix/�ֈړ��������ƁA

$ python setup.py install

�Ǝ��s���ĉ������BDOS�R���\�[���Ŏg�p��������umix.bat��/bin/umix�̗����̃t�@�C��
���p�X�̒ʂ����f�B���N�g���ɃR�s�[���ĉ������B

���o�C�i���ł̃C���X�g�[�����@

�𓀂����f�B���N�g���Ƀp�X��ʂ����A�f�B���N�g���̒��g���܂邲�ƁA�p�X�̒ʂ���
�f�B���N�g���ɃR�s�[���ĉ������B

��Ruby�̗�
  ������
$ umix -l ruby -s StringTest test1 test2 test3

RubyUnit�p�̃e�X�g�R�[�h�𐶐����܂��BStringTest�Ƃ����N���X��
test1, test2, test3�Ƃ������\�b�h���܂݂܂��B
  �����\�b�h�ǉ�

$ umix -a stringtest.rb test4

test4��ǉ����܂��B

���I�v�V����
�@�����L�I�v�V����
  --cout                 : �t�@�C����W���o�͂ɏo��
  --force,     -f        : �����㏑��
  --help,      -h        : �w���v�̕\��
  --lang,      -l <Name> : �o�͌���̐ݒ�
  --reference, -r        : �\�����\�b�h�̊ȈՃ��t�@�����X��\��
  --version,   -v        : �o�[�W�����\��

  ���o�̓I�v�V����
  --add,       -a <Name> : ������TestCase�Ƀ��\�b�h��ǉ�
  --include,   -i <Name> : �t�@�C�����C���N���[�h/�C���|�[�g
  --main,      -m <Name> : �e�X�g���s�t�@�C���𐶐�
  --prefix,    -P + / -  : 'test'�v���t�B�b�N�X��t��(�f�t�H���g)
  --skeleton,  -s <Name> : �e�X�g�X�P���g���N���X��ݒ�

Test::Unit(Ruby) (--lang ruby)
  �T�|�[�g����I�v�V���� -a, -i, -m, -P, -r, -s
CppUnit (--lang cpp)
  �T�|�[�g����I�v�V���� -a, -i, -m, -P, -r, -s
CppUnit-x (--lang cppx)
  �T�|�[�g����I�v�V���� -a, -i, -m, -P, -r, -s
PyUnit (--lang python)
  �T�|�[�g����I�v�V���� -a, -i, -m, -P, -r, -s
JUnit  (--lang java)
  �T�|�[�g����I�v�V���� -a, -i, -P, -r, -s
JsUnit (--lang javascript)
  �T�|�[�g����I�v�V���� -a, -i, -P, -r, -s
NUnit(C#) (--lang csharp)
  �T�|�[�g����I�v�V���� -a, -i, -P, -r, -s
NUnit(VB.net) (--lang vbnet)
  �T�|�[�g����I�v�V���� -a, -i, -P, -r, -s
NUnit(Managed C++) (--lang mcpp)
  �T�|�[�g����I�v�V���� -a, -i, -P, -r, -s
Tcl/tk unit (--lang tcl)
  �T�|�[�g����I�v�V���� -a, -i, -m, -P, -r, -s

���}���`�����K���Ή�
�@��--lang�I�v�V����
--lang(-l)�I�v�V�����Ō�����w�肷�邱�Ƃ��ł��܂��B
���̂Ƃ���ACppUnit(cpp)�ACppUnit-x(cppx)�ARuby��Test::Unit(ruby)�AJUnit(java)�A
PyUnit(python), JsUnit(javascript), Tcl/tk���j�b�g(tcl), NUnit��C#(csharp), 
VB.net(vbnet), Managed C++(mcpp)�ɑΉ����Ă��܂��B

$ umix --lang cpp
�� CppUnit

�@���ȈՌ���w��

������̕����ȒP�ł����A�o�̓t�@�C�����̎w��Ŋg���q��t����Ɗe����̃t�H�[�}�b�g
�Ńt�@�C�����o�͂��܂��B�������ACppUnit-x��.cppx, Managed C++��.mcpp�ł��B

$ umix --skeleton TestString.py
�� PyUnit

���e�X�g���s�t�@�C��

CppUnit�ACppUnit-x�̏ꍇ�́A�ꏏ�Ƀr���h���ĉ������BCppUnit�łł����cocuppa��
�������s���I�v�V�������g�p�ł��܂��B

$ umix --lang cpp --main main --skeleton skeleton
$ c++ -lcppunit main.cpp skeleton.cpp

RubyUnit�APyUnit�́A�������ꂽ�X�N���v�g�̃I�v�V�����Ńe�X�g�R�[�h���w�肵�܂��B

main.cpp�Askeleton.cpp�𐶐����܂��B--force�I�v�V������t���Ȃ��ƁA�����̃t�@�C��
�����݂���ꍇ�̓t�@�C���͍쐬����܂���B

umix�ɂ���č쐬���ꂽ�e�X�g�X�P���g����TestRegisty�ւ̓o�^�R�[�h���܂܂��
���߁A�����Ƀt�@�C�������w�肷�邾���Ńe�X�g���s�����Ƃ��ł���悤�ɂȂ�܂��B

���X�P���g���̏o��

$ umix --skeleton StringTest test1 test2 ...

�e�X�g���\�b�htest1, test2... ����`���ꂽ�e�X�g�̃X�P���g��
stringtest.rb���쐬���܂��B�����̃t�@�C�������݂���ꍇ�͍쐬
����܂���B�쐬�����e�X�g��--main�ō쐬�����X�N���v�g������s
�ł���ق��A�P�̂ł��e�X�g���s�����Ƃ��ł��܂��B

$ ruby stringtest.rb

�����t�@�����X�̕\��

$ umix --reference java

�\�����\�b�h�̊ȈՃ��t�@�����X���\������܂��B���\�b�h��Y���
���܂����ꍇ�ɂ����p�������B���������֗��ł��B
�Z�k�n -r java���g�p�ł��܂��B

�������̃t�@�C���Ƀ��\�b�h��ǉ�

$ umix --add TestString.java testLength

�����̃t�@�C���ɐV�����e�X�g��ǉ����܂��B

��������Ƃ����⑫
�@���e�X�g�̒P�̎��s

C++�ňȊO(Managed C++�͏��O)�͐������ꂽ�e�X�g�P�[�X�P�̂Ŏ��s���邱�Ƃ��ł��܂��B
JUnit�ł̓I�v�V����'a'��t�����AWT��TestRunner���A's'��t�����Swing��TestRunner
�Ŏ��s����܂��B

�@��suite()���\�b�h

CppUnit�ACppUnit-x�̏ꍇ�͏�ɐ�������܂��iC++�̉^��)

���́A����'test'�����Ă���Ǝ������s�����e�X�e�B���O�t���[�����[�N�̏ꍇ
��-P�I�v�V���������Ă����'test'�������I�ɕt������āAsuite()���\�b�h��
��������܂���B-P�I�v�V���������Ă��Ȃ��ꍇ��suite()���\�b�h�����������
�w�肵���e�X�g���\�b�h���S�ēo�^����܂��B

-----
History

2.1
- ���O��umigame����umix�ɕύX
- ���ꂲ�Ƃ̐ݒ�t�@�C����XML�ɕύX�B
- �����n��Python�ɕύX�B
- JsUnit�Ή�(TNX ���z����)
- Tcl/tk���j�b�g�ɑΉ�(TNX ��������)
- NUnit��C#, VB.net, Managed C++�ɑΉ�
- X�C�T���n�b�N�������l������PDF�ŃR���{���[�V�����}��Y�t
  Pattern Weaver�ŏ����܂����B
- py2exe�Ή�
- --prefix�I�v�V�������f�t�H���g�ɂ����B
- --cin�I�v�V�����̍폜

2.0
- --add�I�v�V�����̒ǉ�
- --reference�I�v�V�����̒ǉ�
- --namespace, --super, --abstruct, --separate�I�v�V�����̍폜
- ���O��coppa����umigame�ɕύX
- �I�v�V������(-f && -s || -a)�̎��ɂ̓o�b�N�A�b�v���c���悤�ɂ���

1.7
- JUnit, CppUnit-x, PyUnit�֑Ή��B
- cocuppa��coruppa�𓝍��Bcoppa�ցB
- --main�����BTestRegistry���p�̃e�X�g�R�[�h���o��
- --cin�ǉ��Bstdin����̓��͂ɑΉ��B
- GetoptLong�R�[�h�̏����B--cin�ɑΉ������邽�߂�GetoptLong��p�~�����B

1.5
- RubyUnit�Ή��BRubyUnit�̃R�[�h��f���悤�ɂ���
- --main��p�~�Bruby atest.rb�ƁA���s���ɓn���ꂽ�Ƃ��͎����I��
  �@TestRunner���Ă�
- �o�̓t�@�C���̃T�t�B�b�N�X��.rb�݂̂ɕύX
