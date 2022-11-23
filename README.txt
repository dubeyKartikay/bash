Simple shell by Kartikay Dubey 2021326 CSE:
To run:
make
./sh

internal commands
    cd  --> changes the current working directory, supports ~(partially) and -;
        flags -L,-P
            handled incorrect flags
            handles too many arguments
            handles other errors when changing directories like permission denied
            test cases:

                >pwd
                /home/Kartikay
                >cd ../
                >pwd
                /home

                >ls
                a b                                          (b is set to be inaccesible)
                >cd b
                Permission Denied>

    pwd --> prints out the present working directoy
        flags:
            -L -P
        errors:
            handles too many arguments
            handles inaccesible cwd
        test cases:
                >pwd
                /home/Kartikay
                >cd ../
                >pwd
                /home

    echo --> takes input from stdin and outputs to stdout
        flags:
            -E,-n,--help
        errors:
            incorrect flags handled
            input after --help command handled
        test cases:
            >echo hello world
            hello world 
            >echo -n hello world
            hello world >echo hello world -E
            hello world -E 
            >echo -E hello world
            hello world 
            >


external commands
    ls --> lists all the directories and files in a given directoy
        flags:
            -i,-a,-1
        errors:
            incorrect flags handled
            wrong directory and other ls reated errors handled
        test cases:
            >ls
            a ASN1 a.txt d 
            >ls -a
            a ASN1 a.txt d .. . 
            >ls -a -i -1
            122567 a 
            122546 ASN1 
            122566 a.txt 
            122570 d 
            664 .. 
            115531 . 
            >

    rm  --> removes specified files and empty directories
        flags:
            -v,-d
        errors:
            incorrect flags handled
            invaild input , trying to remove a directory and other errors handled
        test cases:
            >ls
            a ASN1 a.txt d 
            >rm a.txt d a -d -v
            removed 'a.txt'
            removed 'd'
            a : Directory not empty
            >ls
            a ASN1 
            >

    cat --> concatonates files and writes them to stdout, supports reading from stdin using -
        flags:
            -n,-E
        errors:
            incorrect flags handled
            invalid paths handled
        test cases:
            >cat rmBin.c -n -E
            1  #include"commands.h"$
            2  int main(int argc, char * argv[]){$
            3      rm(argv,argv[0]);$
            4      $
            5  }
            >cat lsBin.c rmBin.c -n -E
            1  #include"commands.h"$
            2  int main(int argc, char * argv[]){$
            3      ls(argv,argv[0]);$
            4      $
            5  }
            5  #include"commands.h"$
            6  int main(int argc, char * argv[]){$
            7      rm(argv,argv[0]);$
            8      $
            9  }
            >

    date --> prints out the current date and time in localtime for UTC, can also the used to see the last modified time of a file using the -r flag
        flags:
            -u,-r
        errors:
            no file provided when using the flag -r handled
            incorrect flags handled
        test cases:
            >date
            Wed Oct 26 21:34:45 2022
            >date -u
            Wed Oct 26 16:04:47 2022
            >date -r lsBin.c
            Tue Oct 25 23:32:10 2022
            >

    mkdir --> creates empty directories and allowes you to set thier modes 
                note: mode specified may or may not be followed based on the umask value of the shell (mode & umask & 0777)
        flags:
            -v,-m
        errors:
            no directories provided to mkdir handled
            invalid paths to directores and other mkdir errors handled
        test cases:
            >ls
            a ASN1 
            >mkdir b c ../d -m 555 -v
            created directoy b
            created directoy c
            mkdir: ../d : File exists
            >ls ../
            e plot_graph.py mak  d OS  
            >ls
            a ASN1 b c 
            >

    

    