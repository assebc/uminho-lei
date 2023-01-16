using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.ComponentModel.DataAnnotations;
using webOnlyFeiras.Model;

namespace webOnlyFeiras.Areas.Identity.Pages.Account
{
    public class LoginModel : PageModel
    {
        private readonly SignInManager<Utilizador> _signInManager;
        private readonly UserManager<Utilizador> _userManager;


        public LoginModel(SignInManager<Utilizador> signInManager, UserManager<Utilizador> userManager)
        {
            _signInManager = signInManager;
            _userManager = userManager;
        }

        [BindProperty]
        public InputModel Input { get; set; }
        public string ReturnUrl { get; set; }
        public void OnGet()
        {
            ReturnUrl = Url.Content("~/");
        }
        public async Task<IActionResult> OnPostAsync()
        {
            ReturnUrl = Url.Content("~/");
            if (ModelState.IsValid)
            {
                var user = await _userManager.FindByEmailAsync(Input.Email);
                if (user != null)
                {
                    var result = await _signInManager.PasswordSignInAsync(user, Input.Password,true, lockoutOnFailure: false);
                    if (result.Succeeded)
                    {
                        return LocalRedirect(ReturnUrl);
                    }
                    else
                    {
                        ModelState.AddModelError(string.Empty, "Invalid login attempt.");
                        return Page();
                    }
                }
            }
            return Page();
        }

        public class InputModel
        {
            [Required]
            [EmailAddress]
            public string Email { get; set; }
            [Required]
            [DataType(DataType.Password)]
            public string Password { get; set; }

        }

    }
}
