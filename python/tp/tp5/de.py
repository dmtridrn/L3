import random as r

def lancer_de() -> int:
    val = r.randint(1,6)
    return val

def fin_partie(des: dict) -> int:
    score = 0
    check = {i:0 for i in range(1,7)}
    for i in des.values():
        check[i] += 1
    for i in check:
        match check[i]:
            case 2: 
                score += 20 
                print("Paire: +20")
            case 3: 
                score += 40
                print("Brelan: +40")
            case 4: 
                score += 60
                print("Carre: +60")
            case 5: 
                score += 80
                print("Quinte: +80")
    if len(set(des.values())) == len(des):
        print("SUIIIIIIIITE: +100")
        score +=  100
    return score

def relancer(des: dict, idx: str) -> dict:
    liste_des = idx.split(" ")
    for i in liste_des:
        des["d"+i] = lancer_de()
    print(des)
    return des

if __name__ == "__main__":
    des = {"d1": 0, "d2": 0, "d3": 0, "d4": 0, "d5": 0}
    essais = 1
    for i in des:
        des[i] = lancer_de()
    print(des)
    while(essais < 3):
        idx = input("Quel(s) de(s) voulez vous relancer ? Syntaxe: (1-5) (1-5)...\n")
        if idx == "0":
            break
        des = relancer(des, idx)
        essais += 1
    score = fin_partie(des)
    print(f"Score final: {score}")