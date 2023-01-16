using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class CandidaturaParaMarca
    {
        public enum EstadoCandidatura
        {
            Pendente,
            Aceite,
            Recusada
        }
        [Key]
        public int IdCandidaturaMarca { get; set; }
        [Required]
        public Utilizador Responsavel { get; set; }
        [Required]
        public DateTime Data { get; set; }
        [Required]
        public Marca Marca { get; set; }
        [Required]
        public EstadoCandidatura Estado { get; set; }
    }
}
