with open("out/nonces.log","r") as f:
    lines=f.readlines()
    for line in lines:
        if len(line)-3<62:
            print("lenth:",len(line)-3)
        # print("lenth:",len(line)-3)
        
