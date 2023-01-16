using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.ComponentModel.DataAnnotations;
using System.Data;
using webOnlyFeiras.Model;

namespace webOnlyFeiras.Areas.Identity.Pages.Account
{

    public class RegisterModel : PageModel
    {
        private readonly SignInManager<Utilizador> _signInManager;
        private readonly UserManager<Utilizador> _userManager;
        private readonly RoleManager<IdentityRole> _roleManager;


        public RegisterModel(SignInManager<Utilizador> signInManager, UserManager<Utilizador> userManager, RoleManager<IdentityRole> roleManager)
        {
            _signInManager = signInManager;
            _userManager = userManager;
            _roleManager = roleManager;
        }

        [BindProperty]
        public InputModel Input { get; set; }
        public string ReturnUrl { get; set; }
        public string Errors { get; set; } = String.Empty;

        public void OnGet()
        {
            ReturnUrl = Url.Content("~/");
        }

        public async Task<IActionResult> OnPostAsync()
        {
            ReturnUrl = Url.Content("~/");
            if (ModelState.IsValid)
            {
                var user = new Utilizador
                {
                    Email = Input.Email,
                    DataNascimento = Input.DataNascimento,
                    PhoneNumber = Input.PhoneNumber,
                    Nome = Input.NomeCompleto,
                    UserName = Input.Username
                };
                var result = await _userManager.CreateAsync(user, Input.Password);
                var userRole = new IdentityRole(Input.Role);
                await _roleManager.CreateAsync(userRole);
                var addUserRoleResult = await _userManager.AddToRoleAsync(user, Input.Role);
                if (result.Succeeded)
                {
                    await _signInManager.SignInAsync(user, isPersistent: false);
                    return LocalRedirect(ReturnUrl);
                }
            }
            return Page();
        }

        public class InputModel
        {
            [Required(ErrorMessage = "Email inválido.")]
            [EmailAddress]
            public string Email { get; set; }
            [Required(ErrorMessage = "Palavra-passe inválida.")]
            [DataType(DataType.Password)]
            public string Password { get; set; }
            [Required(ErrorMessage = "Nome inválido.")]
            public string NomeCompleto { get; set; }
            [Required(ErrorMessage = "Nome de usuário inválido.")]
            public string Username { get; set; }
            [Required]
            public DateTime DataNascimento { get; set; }

            public string PhoneNumber { get; set; } = string.Empty;

            public string Role { get; set; } = "Utilizador";

        }
    
    }
}