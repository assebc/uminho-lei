using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class Banca
    {
        [Key]
        public int BancaId { get; set; }
        [Required]
        public string PathFotografia { get; set; } = String.Empty;
        public string Descricao { get; set; } = String.Empty;

    }
}
