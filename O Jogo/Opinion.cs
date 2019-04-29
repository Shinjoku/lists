public static class Opinion{
    
    private static int opinion = 0;

    public static Opinion(){
        opinion = 0;
    }
    
    public static void incOpinion()
        opinion++;
    }    
    
    public static void decOpinion(){
        opinion--;
    }
    
    public static int getOpinion(){
        return opinion;
    }
    
}