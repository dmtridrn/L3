package tp2;

public abstract class Diplome {
        public final String intitule;
        public final Mention mention;
        public final int annee;

        public Diplome(String intitule, Mention mention, int annee) {
            this.intitule = intitule;
            this.mention = mention;
            this.annee = annee;
        }
    }

    final class Bac extends Diplome {
        public Bac(String intitule, Mention mention, int annee) {
            super(intitule, mention, annee);
        }
    }

    final class Daeu extends Diplome {
        public Daeu(String intitule, Mention mention, int annee) {
            super(intitule, mention, annee);
        }
    }

    final class Licence extends Diplome {
        public Licence(String intitule, Mention mention, int annee) {
            super(intitule, mention, annee);
        }
    }

    final class Master extends Diplome {
        public Master(String intitule, Mention mention, int annee) {
            super(intitule, mention, annee);
        }
    }

    final class DiplomeInge extends Diplome {
        public DiplomeInge(String intitule, Mention mention, int annee) {
            super(intitule, mention, annee);
        }
    }

    final class Doctorat extends Diplome {
        public Doctorat(String intitule, Mention mention, int annee) {
            super(intitule, mention, annee);
        }
    }

    enum Mention {
        PASSABLE, ASSEZ_BIEN, BIEN, TRES_BIEN, FELICITATIONS;
    }
