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

    cy.get('#sentence_root > span > span:nth-child(2)')
      .should('be.visible') // Ensure the element is visible
      .should('have.css', 'background-color', 'rgb(250, 145, 137)'); // Check for red background

    cy.get('#left-column > div > div > div.tab-pane.ng-scope.active > div > kwic > div > div.table_scrollarea > table > tbody > tr:nth-child(9) > td.left.ng-scope > kwic-word:nth-child(2) > span > span')
      .should('be.visible') // Ensure the element is visible
      .should('have.css', 'background-color', 'rgb(209, 189, 255)'); 
  });
});
