#!/bin/sh
rm -f xk_index.html xk_response.html
wget -q 'http://xk.fudan.edu.cn/xk/' --load-cookies=cookies.txt --save-cookies=cookies.txt --keep-session-cookies -O xk_index.html
wget -q 'http://xk.fudan.edu.cn/xk/image.do' --load-cookies=cookies.txt --save-cookies=cookies.txt --keep-session-cookies -O xk_captcha.jpg
X=`../../sample/ocr_single/ocr_single xk_captcha.jpg`
mv xk_captcha.jpg data/${1}.jpg
wget -q 'http://xk.fudan.edu.cn/xk/loginServlet' --load-cookies=cookies.txt --keep-session-cookies --save-cookies=cookies.txt "--post-data=Submit2=提交&studentId=123&rand=${X}&password=456" -O xk_response.html
# R=0 - other error
# R=1 - ocr ok
# R=2 - ocr error
R=0
if grep 'Log-in failed' xk_response.html; then
    R=1
elif grep '验证码不正确' xk_response.html; then
    R=2
fi
echo ${1} ${X} ${R}
echo ${1} ${X} ${R} >> testlog.txt

