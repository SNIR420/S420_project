class Simulateur{

    public:
        explicit Simulateur() ;
        double getTwa();
        double getTws();
        double getAngleBome();
        double getSpeed();
        void setAngleVentJeu(double twa);
        void setTws(double tws);
        void setWave(int force); // échelle de beaufort

    public slots:
        void info(const QString& src, const QString& msg ) ;
} ;