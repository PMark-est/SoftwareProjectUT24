describe('Search test', () => {
  it('should type a period and click search button', () => {
    // Visit the page with the input field and search button
    cy.visit('andmebaas.zapto.org');

    // Type '.' into the input field
    cy.get('#simple_text > div > div:nth-child(2) > div > input')
      .should('be.visible')   // Ensure the element is visible
      .type('.');

    // Click the search button
    cy.get('#sendBtn').click();

    cy.get('#left-column > div > div > div.tab-pane.ng-scope.active > div > kwic > div > filter > span > uib-dropdown > button')
    .should('be.visible')
    .click();

  // Wait for the dropdown to be open
  cy.get('#left-column > div > div > div.tab-pane.ng-scope.active > div > kwic > div > filter > span > uib-dropdown > ul')
    .should('exist') // Ensure the dropdown exists in the DOM
    .should('be.visible'); // Ensure it is visible before continuing

  // Select the "vorm" option in the dropdown
  cy.get('#left-column > div > div > div.tab-pane.ng-scope.active > div > kwic > div > filter > span > uib-dropdown > ul > li:nth-child(3) > a')
    .click({ force: true }); 
  });
});
