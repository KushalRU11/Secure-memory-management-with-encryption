RED="\e[31m"
ORANGE="\e[33m"
BLUE="\e[94m"
GREEN="\e[92m"
STOP="\e[0m"
RED="$(printf '\033[31m')"  GREEN="$(printf '\033[32m')"  ORANGE="$(printf '\033[33m')"  BLUE="$(printf '\033[34m')"
MAGENTA="$(printf '\033[35m')"  CYAN="$(printf '\033[36m')"  WHITE="$(printf '\033[37m')" BLACK="$(printf '\033[30m')"
REDBG="$(printf '\033[41m')"  GREENBG="$(printf '\033[42m')"  ORANGEBG="$(printf '\033[43m')"  BLUEBG="$(printf '\033[44m')"
MAGENTABG="$(printf '\033[45m')"  CYANBG="$(printf '\033[46m')"  WHITEBG="$(printf '\033[47m')" BLACKBG="$(printf '\033[40m')"
RESETBG="$(printf '\e[0m\n')"
animate_text() {
    text="SECURE MEMORY MANAGEMENT WITH ENCRYPTION"
    length=${#text}

    for ((i = 0; i < length; i++)); do
        clear
        printf "${ORANGE}"
        printf "%s${STOP}\n" "$(figlet -w 200 -f small "${text:0:i}")"
        sleep 0.05
    done

    for ((i = length; i >= 0; i--)); do
        clear
        printf "${ORANGE}"
        printf "%s${STOP}\n" "$(figlet -w 200 -f small "${text:0:i}")"
        sleep 0.05
    done
}


# Function to compile memory allocation related files

compile_memory_allocation() {

    printf "${RED}"

    figlet -w 200 -f small "Memory Allocation"

    gcc -g -c mm.c -o mm.o

    gcc -g -c gluethread/glthread.c -o gluethread/glthread.o

}



# Function to compile test data related files

compile_test_data() {

    printf "${ORANGE}"

    figlet -w 200 -f small "Test Data"

    gcc -g -c testapp.c -o testapp.o -lssl -lcrypto

    gcc -g gluethread/glthread.o mm.o testapp.o -o exe -lssl -lcrypto

}



# Function to handle memory allocation test case

memory_allocation_test() {

    compile_memory_allocation

    compile_test_data

    printf "${ORANGE}"

    ./exe encrypt

}



# Function to handle show data test case

show_data_test() {

    compile_test_data

    printf "${ORANGE}"

    ./exe decrypt

}



# Function to handle test cases at the starting

run_test_cases() {

    compile_test_data

  
    gcc -g -c test2.c -o test2.o -lssl -lcrypto

    gcc -g gluethread/glthread.o mm.o test2.o -o exe -lssl -lcrypto

    ./exe

}



# Main menu

while true; do

    clear
    animate_text
    clear
    
    printf "${GREEN}"
    
    printf "=================================\n"

    printf "${ORANGE}"

    text=""
    length=${#text}

    for ((i = 0; i <=length; i++)); do
        clear
        printf "${ORANGE}"
        printf "%s${STOP}\n" "$(figlet -w 200 -f small "${text:0:i}")"
        sleep 0.05
    done
    printf "${BLUE}"
    
    text="Memory-Management"
    length=${#text}

    for ((i = 0; i <=length; i++)); do
        clear
        printf "${ORANGE}"
        printf "%s${STOP}\n" "$(figlet -w 200 -f small "${text:0:i}")"
        sleep 0.05
    done
    clear
    printf "${GREEN}"

    printf "=================================\n"

    printf "${ORANGE}"

    figlet -w 200 -f small ""

    printf "${ORANGE}"

    figlet -w 200 -f small "Memory Management"

    printf "${GREEN}"

    printf "=================================\n"

    printf "${STOP}"
    
    printf "\n${RED}"

    figlet -w 200 -f small "    Options"

    printf "${STOP}"

    printf "${ORANGE}"
    echo "     -----------------------------------------"
    
    echo "     |${RED}[${WHITE}01${RED}]${ORANGE}- Memory Allocation Test Case      |"
    echo "     |${RED}[${WHITE}02${RED}]${ORANGE}- Show Data Test Case              |"
    echo "     |${RED}[${WHITE}03${RED}]${ORANGE}- Run Test Cases at the Starting   |"
    echo "     |${RED}[${WHITE}03${RED}]${ORANGE}- Exit                             |"
    echo "     -----------------------------------------"
    printf "${STOP}"

    

    read -p "Enter your choice: " choice



    case $choice in

        1) memory_allocation_test ;;

        2) show_data_test ;;

        3) run_test_cases ;;

        4) exit ;;

        *) echo "Invalid option. Please choose again." ;;

    esac

    read -p "Press Enter to continue..."

done

