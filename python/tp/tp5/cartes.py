import random

def newListe(n):
    return [random.randint(-10, 20) for _ in range(n)]

def QuiGagne(L1, L2):
    score1 = sum(L1)
    score2 = sum(L2)
    print(f"\nScore Joueur: {score1} | Score Ordi: {score2}")
    if score1 > score2:
        return "Félicitations, vous avez gagné !"
    elif score2 > score1:
        return "L'ordinateur a gagné. Dommage !"
    else:
        return "Égalité parfaite !"

def ChoixOrdi(L, dejaelim):

    if not dejaelim:
        pourri = min(L)
        if pourri < -5:
            return f"{L.index(pourri)}"
    

    if L[0] >= L[-1]:
        return "G"
    return "D"

def Cartes(n):

    board = newListe(n)
    joueur_main = []
    ordi_main = []
    joueur_elim = False
    ordi_elim = False
    historique = []

    try:
        reponse = input("Voulez-vous commencer ? (o/n) : ").lower()
        tour_joueur = True if reponse == 'o' else False
        
        while board:
            historique.append((list(board), list(joueur_main), list(ordi_main), joueur_elim, ordi_elim, tour_joueur))
            
            print(f"\nPlateau actuel : {board}")
            
            if tour_joueur:
                print("--- À VOUS DE JOUER ---")
                print("Options: G (gauche), D (droite), index i (ex: '2'), U (Undo)")
                coup = input("Votre choix : ").strip().upper()
                
                if coup == 'U':
                    if len(historique) > 1:
                        historique.pop()
                        etat_prec = historique.pop()
                        board, joueur_main, ordi_main, joueur_elim, ordi_elim, tour_joueur = etat_prec
                        print("<<< Retour en arrière effectué")
                        continue
                    else:
                        print("Impossible de revenir en arrière.")
                        continue
                
                try:
                    if coup == 'G':
                        joueur_main.append(board.pop(0))
                    elif coup == 'D':
                        joueur_main.append(board.pop(-1))
                    elif coup.isdigit():
                        if joueur_elim:
                            raise Exception("Vous avez déjà utilisé votre élimination !")
                        idx = int(coup)
                        if 0 <= idx < len(board):
                            board.pop(idx)
                            joueur_elim = True
                        else:
                            raise IndexError
                    else:
                        raise ValueError
                except (ValueError, IndexError):
                    print("Saisie invalide ! Utilisez G, D ou un index valide.")
                    historique.pop()
                    continue
                except Exception as e:
                    print(e)
                    historique.pop()
                    continue
            
            else:
                print("--- TOUR DE L'ORDINATEUR ---")
                choix = ChoixOrdi(board, ordi_elim)
                if choix == 'G':
                    print("L'ordi prend à Gauche.")
                    ordi_main.append(board.pop(0))
                elif choix == 'D':
                    print("L'ordi prend à Droite.")
                    ordi_main.append(board.pop(-1))
                else:
                    idx = int(choix)
                    print(f"L'ordi élimine la carte à l'index {idx} !")
                    board.pop(idx)
                    ordi_elim = True
            
            tour_joueur = not tour_joueur

        print("\n--- FIN DE PARTIE ---")
        print(QuiGagne(joueur_main, ordi_main))

    except KeyboardInterrupt:
        print("\n\nPartie interrompue par l'utilisateur (Ctrl-C). À bientôt !")

Cartes(6)