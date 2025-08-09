option="k"
iter=0

while [[ $option != "y" && $option != "Y" && $option != "n" && $option != "N" ]]
do
    if [[ $iter -gt 0 ]]; then
        echo "[?] Unknown input."
    fi

    read -p "[*] Do you want to delete packages after install? [y/n] " option
    ((iter++))
done



sudo cp -r ./include/GameEngine /usr/include/
mkdir ~/.gameengine
sudo cp -r ./defaults/* ~/.gameengine/


sudo cp -r ./lib/libgameengine.so /usr/lib/

if [[ $option -eq "y" ]];
then
    echo "[*] Deleting packages..."
    cd ../ && rm -rf ./Game-Engine
fi

echo "[*] Library Game-Engine installed."
