package tp2;

public class CurriculumVitae {
    private Bac bac;
    private Daeu daeu;
    private Licence licence;
    private Master master;
    private DiplomeInge diplomeInge;
    private Doctorat doctorat;

    private CurriculumVitae() {
    }
    
    public static CVBuilder builder() {
        return new CVBuilder();
    }

    public static class CVBuilder {
        private Bac bac;
        private Daeu daeu;
        private Licence licence;
        private Master master;
        private DiplomeInge diplomeInge;
        private Doctorat doctorat;

        public CVBuilder bac(Bac bac) {
            this.bac = bac;
            return this;
        }

        public CVBuilder daeu(Daeu daeu) {
            this.daeu = daeu;
            return this;
        }

        public CVBuilder licence(Licence licence) {
            this.licence = licence;
            return this;
        }

        public CVBuilder master(Master master) {
            this.master = master;
            return this;
        }

        public CVBuilder diplomeInge(DiplomeInge diplomeInge) {
            this.diplomeInge = diplomeInge;
            return this;
        }

        public CVBuilder doctorat(Doctorat doctorat) {
            this.doctorat = doctorat;
            return this;
        }
        
        public CurriculumVitae build() {
            CurriculumVitae cv = new CurriculumVitae();
            cv.bac = this.bac;
            cv.daeu = this.daeu;
            cv.licence = this.licence;
            cv.master = this.master;
            cv.diplomeInge = this.diplomeInge;
            cv.doctorat = this.doctorat;
            return cv;
        }
    }
    
    public Bac getBac() {
        return bac;
    }
    
    public Daeu getDaeu() {
        return daeu;
    }
    
    public Licence getLicence() {
        return licence;
    }
    
    public Master getMaster() {
        return master;
    }
    
    public DiplomeInge getDiplomeInge() {
        return diplomeInge;
    }
    
    public Doctorat getDoctorat() {
        return doctorat;
    }
}