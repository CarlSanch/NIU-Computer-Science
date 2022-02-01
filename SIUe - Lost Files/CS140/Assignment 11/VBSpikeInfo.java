
public class VBSpikeInfo
{
   String name;
   int spikesAttempted;
   int errors;
   int kills;
   
   public VBSpikeInfo()
   {
       
    }
    
   public VBSpikeInfo(String name, int spikesAttempted, int errors, int kills)
   {
       this.name = name;
       this.spikesAttempted = spikesAttempted;
       this.errors = errors;
       this.kills = kills;
    }
    
   public int getKills()
   {
       return kills;
    }
    
   public double percentErrors()
   {
       double percentErrors;
       
       percentErrors = ((errors/1.0) / spikesAttempted) * 100;
       
       return percentErrors;
    }
    
   public double percentKills()
   {
       double percentKills;
       
       percentKills = ((kills/1.0) / spikesAttempted) * 100;
       
       return percentKills;
    }
    
   public String toString()
   {
      
      String output = String.format("%-16s%9d%10d%15.2f", name, spikesAttempted, kills, percentKills());
      
      return output;
    } 
}
