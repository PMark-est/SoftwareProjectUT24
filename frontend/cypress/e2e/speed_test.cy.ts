describe('Search test with content appearance check', () => {
  it('should check if content appears within 2 seconds after button click', () => {
    // Visit the page with the input field and search button
    cy.visit('andmebaas.zapto.org');

    // Type '.' into the input field
    cy.get('#simple_text > div > div:nth-child(2) > div > input')
      .should('be.visible')   // Ensure the element is visible
      .type('.');

    // Click the search button
    cy.get('#sendBtn').click();

    // Wait for the specific element to appear within 2 seconds
    cy.get('#left-column > div > div > div.tab-pane.ng-scope.active > div > kwic > div > div.table_scrollarea > table > tbody > tr:nth-child(12) > td.left.ng-scope > kwic-word:nth-child(4)', { timeout: 2000 })
      .should('be.visible')
      .click();

    // Assert that the popup appears after the element click
    cy.get('#sentence_root > span > span', { timeout: 2000 })
      .should('be.visible');
  });
});