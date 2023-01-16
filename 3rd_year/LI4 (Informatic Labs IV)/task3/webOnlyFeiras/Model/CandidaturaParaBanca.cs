using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class CandidaturaParaBanca
    {
        public enum EstadoCandidatura
        {
            Pendente,
            Aceite,
            Recusada
        }
        [Key]
        public int IdCandidaturaBanca { get; set; }
        [Required]
        public Utilizador Responsavel { get; }
        [Required]
        public DateTime Data { get; set; }
        [Required]
        public Banca Banca { get; set; }
        [Required]
        public Boolean PatrocinaFeira { get; set; }
        [Required]
        public EstadoCandidatura Estado { get; set; }

    }
}
