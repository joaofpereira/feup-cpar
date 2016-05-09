1. Configuracao do ssh:  (o rsh ja nao e suportado)
   A configuracao e ao nivel do utilizador

a) Se nao existir o directorio ~/.ssh   cria-lo.
b) cd ~/.ssh
c) ssh-keygen -t dsa
   at prompt, hit enter, saving file as id_dsa
   at the prompts, hit enter (2x) when asked for a passphrase

d) cat id_dsa.pub >> authorized_keys

e) Copiar o ficheiro authorized_keys para o computador remoto e coloca-lo
   no directorio ~/.ssh
   Nota: o ficheiro id_dsa.pub e a chave publica por utilizador e computador.
   Por isso se pretendemos aceder ao mesmo computador remoto a partir de sitios
   diferentes, devemos copiar id_dsa.pub para o computador remoto e adicionar este
   ficheiro ao authorized_keys ja existente. Neste caso o comando d) seria feito
   no computador remoto.


2. Verificar a ligacao por ssh

   ssh 192.168.xxx.xxx ls
   devera devolver o conteudo do home directory remoto sem perguntar a password.
   ou: ssh 192.168.xxx.xxx -n echo $SHELL


3. Compilar programa com MPI

   mpiCC.openmpi -o prog prog.cpp

4. Criar hostfile que contém a lista de maquinas onde deve iniciar o mpi
   Exemplo da hostfile:
   192.168.xxx.xxx cpu=4
   192.168.xxx.xxz

5. Correr programa com mpi
   mpirun --hostfile hostfile -np 4 prog
