#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --prefix=dir      directory in which to install
  --include-subdir  include the Calc-1.0.1-Linux subdirectory
  --exclude-subdir  exclude the Calc-1.0.1-Linux subdirectory
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "Calc Installer Version: 1.0.1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage 
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version 
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'

____cpack__here_doc____
    echo
    echo "Do you accept the license? [yN]: "
    read line leftover
    case ${line} in
      y* | Y*)
        cpack_license_accepted=TRUE;;
      *)
        echo "License not accepted. Exiting ..."
        exit 1;;
    esac
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the Calc will be installed in:"
    echo "  \"${toplevel}/Calc-1.0.1-Linux\""
    echo "Do you want to include the subdirectory Calc-1.0.1-Linux?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/Calc-1.0.1-Linux"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

tail $use_new_tail_syntax +142 "$0" | gunzip | (cd "${toplevel}" && tar xf -) || cpack_echo_exit "Problem unpacking the Calc-1.0.1-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� S��Y �Zp�u^ $ER��H��b�C%!���b�EBdH�IZCǪ�  ��@�
�Hzh;A�L�LO⨉f��ǓNS�n$��ªq[��r�I]���%�tk{8�dt������Nr�If�8������o���],�g"��;Cʸs�\r�\�)%1u��n��nsw�ܞvO�Kr���ݭDr]w��I+�u%�L*���\�X�?�.6��DG��݃~�_]yeb����dbL�L~�9�P��P:�qx�@4��F*MDb�Օ��z�Q�8���]�����G���Cǿ���^���~ۀO�y;z}
�N$�=�����]�����%�Ef`�t'�?<�%6�c#��o�$�J,�H;C�o���흭��oomk+���6n���7Un���nwunq��ѪH.�i~��ao��{�O��}A,F���ON:��/iͭ���sK+��9_p��f�=�������f{�ً������Ͼ�9/e��f�C�	�Y���gTƿ�[����[;�;��?{۲�������g|l��7�k�1�|��Y���XD]�Ѕlfe��[��Z��hwژ/�Q�y��XM�8H�������N��8 M�f�W�枞OH�7�m��qz��R����js�I��ш�)����D�ױ�����ئ���]S��|ζ�>I�����=�e�;i>!�6Ĕ�V�Vu�1-�ߧ��L�PB#4URZ:ΞR�xȩD�⌄�q���Mj��V�)�����K$���V�����>��ˣ��DԤ;��u��/p��
x��_c��Whi9v�j,��{O7 ��W,���8ڴ�ǌ��F��3�r��D��g����o1�	h������Ha���(q�`��4wKOw��:u��&�ab�~](8-�%�w���?�<Կ�ֿ���=�G��	�7�h�TK��Z�>��WX�_��B��Z@ WB^ϙ�9,�8L=�����*�����	��M�7I~~ ���숳
�+,p󽳣���'�����5J��Ll|������b�W����|��o&���%�%˱d,S(�q�2]�XX$����V%"r$J������]tW"�ܽ�;(�Yߩ�䱩)y2�J'Ԍr@��R�E}�����d%�)�@�GO@��m$��>$iy��D <(���[�h"�ߝ�<��2U�5���}}����O��X2-�5�'@k����7�{U\����8m�x�2ᩐ�kp���ؼ��������S;��9�>���s�7p���=�<?:����p�|#'?��������or����|6����٩��4qv���W�ٸ��w����o"K\�2�y���������v�������Z=����A�iˎ���
��{�[���.�.yɇ�f�R��tM��BX�K��`�!݀0K�ݛq��ң8T��CV���Y�-1uÆ4�~s��ׅz](�R���������S6[�r�@}/+U�����4�rAA�V�g��0'�'\�tx6�#-�X"3�2�����q���V�6T�FOb�<k�,fd�Gǿ��~�gs����G~~�_M�3�"T��*�?�8Wi۸������%��`�j��2k��z,���C�����+ϼV��s\��ƿ��ï�<��߽����_���}=??���f߳�߳�_x�u��g��Ň�>��/�Q�����v*��W��G����bn�-�Z�ߵ�s�~�j��,VyxPū�R��_B�!ćVk8[�>��ər������\�a؀�l�k�
�����Q�������#Â��X��
c�m�{��,���U���ig?�s��C�K(�E<e��[��џI��K�a=�F�:6��q�V"�}�Z�?'�>#E�������X,�DS=�P:M[��
6��{����-6��}�޺��1h�	�%��X8,��sf-��`e2����"�tF��"v��H,!g��l�CJHS�e���<�N�<�Fܱ �^Q�l�[���v�34Խ- ��m<4$�9=�>eWO�v�lh�+1`vU��m��$su�f��c?��:�e��+����(��Re�B��z������?X;��s⫈�$,q8��n�p~vq8�uq8??y9|��9�?��q�:�p���9_�x�>,�E��x��O�O��*$������^�O����K��q��J�)��Ry;�ДK�*��r�Ò����/��DKGT��i��T��I��U�?�w�&U�߀��.S��j �����������0c����d���1*�����?[����+��Sj�x������Z����f�u�jR��9	�'�v�g���[Τ�Fk��ƚ����h��S��2*[Τ^�i� }�Aqw�>9::ꬽ�^l�O�)��@�J�z�
���pQ�sϟ>�����������S��rǡ��|�z������L���%e|o��l��o�8�� `� ���.��.d����F)�:w���#t�Z��TV����8``d�"�ۛ^��	Q�5zM�^���%e�P�(8�4:~�v���m��3o:�F���n�W�D����GH(��*M�����vo�}绂�^��^d��?q����b�������lp�����:�}�7�Zw������ϝK����D�r��.8iZ�ORpVij�lr�n�uR�ϴ;�Q?�3+9e��u�wa�=WN���22�c����k�m^�i]-cɄD�D�خq���yh�6Y�����iz�@��J�'i�-����Ҵ���4��i	mս6��Gg`G�Eg �|�Yx������MV���Y������1B�pӐ��fȇ7:N�"@G��×����3��f�v�Z=�Y#��z|�C]a�<Bquou�K�/�k�3����%���PM��g��o�K��6�ￍ��/����ٌ��ߌUȳ�w�sʛ�䒐�5��5�J5��1���ϟF���g{��H?������3�����&��I�_�?�J�Y_ewV잟�O��>�(�C����������c�T�瘫0��L�c��QL�cz?w��ٗ#��84��a�	oQBcȍ%2ΑL,i�E�ʍ����9����TIi9������)1SA|��+P$=`�Z=W�Qk���#�<GX ;�%w�SjᡉX��T��6
ga�ߚ *m����=�{(A^��]G������V/	�fQe^+�oE�I��a�{���?����~q6�kDuWs����$f��a��C�����f
|Zh0�� ����g�yN����#�\�x6_L�~��o'����hm�������Il?V�{}6�1A6?�~��>�]��*��~��(�H|�YA��Q���>;�����u�pB�b��AA��G��`���G�q����ԿN���1A?���AA^,�G��8ꏣ�V�Ê�����\K���� �K�/��X�����B}W����?C�w����������1���|v��R��Y�_�>�_�ˏ���"�{�a�߷�/�WA��'�������7��W5L�E�����W)_F�w,�y�쫔�k��̓D�;ɻ�*e�#Z��B��*�����5���:i���g�K�u͈���/��!#��t�_�L���z`�+��/����*}^6���^��||��������3#ސ���}�1���b�ך��*}0�ʏo^��|��_]�i㠚��О0�̾�ڠ���GU���T��|X��B�w�����mظ��g�q
��U�;��E��	�|Y��ɑ��oY��0���Я��(����#B��C;v<3k����Ε�m�������������U�ͤ�U��a\�n��{��>�����3���v
�ş[����[��E��E��I�y����E��M����[,��y�q�B��v���v�8�sv�8��<	��Y���a_�w����a��r��3�-����<N{�ag���<�L¡x����pJI+��Qg��r���~9���k�v�pL$)�œ#������Pf��3�d<�D#Ύ��Vr,2��hG�Hfb� +Ƿ�W����{�O���/%������kE5���
��3F�vo�>����}��`/_)�@�R�Z��0�{���NY����c��Wf�|L[�7���b6�e��c7����`�R1g�l:�P�1�/����^���A-�m�	��˅�����r��T�"�HE*R��T�"�HE*R�~����� P  