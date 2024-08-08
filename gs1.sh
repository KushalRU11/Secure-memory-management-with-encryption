text="Blue-Devil"
length=${#text}
for ((i = 0; i <=length; i++)); do
        clear
        printf "${BLUE}"
        printf "%s${STOP}\n" "$(figlet -w 200 -f small "${text:0:i}")"
        sleep 0.3
done
